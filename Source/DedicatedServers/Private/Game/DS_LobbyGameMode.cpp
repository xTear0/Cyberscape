// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Game/DS_LobbyGameMode.h"
#include "Game/DS_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Lobby/DS_LobbyPlayerInfo.h"
#include "Lobby/DS_LobbyState.h"
#include "Player/DS_PlayerController.h"
#if WITH_GAMELIFT
#include "Game/DS_GameInstanceSubsystem.h"
#include "DedicatedServers/DedicatedServers.h"
#endif
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_LobbyGameMode.cpp_Functions
ADS_LobbyGameMode::ADS_LobbyGameMode()
{
    bUseSeamlessTravel = true;
    LobbyStatus = EDS_LobbyStatus::WaitingForPlayers;
    MinPlayers = 1;
    LobbyCountdownTimer.Type = EDS_CountdownTimerType::LobbyCountdown;
}

void ADS_LobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
    CheckAndStartLobbyCountdown();
}

void ADS_LobbyGameMode::InitSeamlessTravelPlayer(AController* NewController)
{
    Super::InitSeamlessTravelPlayer(NewController);
    CheckAndStartLobbyCountdown();

    if (LobbyStatus != EDS_LobbyStatus::SeamlessTraveling)
    {
        AddPlayerInfoToLobbyState(NewController);
    }
}

void ADS_LobbyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
    CheckAndStopLobbyCountdown();
    RemovePlayerSession(Exiting);
    if (LobbyStatus != EDS_LobbyStatus::SeamlessTraveling)
    {
        RemovePlayerInfoFromLobbyState(Exiting);
    }
}

void ADS_LobbyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId,
    FString& ErrorMessage)
{
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

    const FString PlayerSessionId = UGameplayStatics::ParseOption(Options, TEXT("PlayerSessionId"));
    const FString Username = UGameplayStatics::ParseOption(Options, TEXT("Username"));

    TryAcceptPlayerSession(PlayerSessionId, Username, ErrorMessage);
}

FString ADS_LobbyGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId,
    const FString& Options, const FString& Portal)
{
    FString InitializedString = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

    const FString PlayerSessionId = UGameplayStatics::ParseOption(Options, TEXT("PlayerSessionId"));
    const FString Username = UGameplayStatics::ParseOption(Options, TEXT("Username"));

    if (ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(NewPlayerController); IsValid(DS_PlayerController))
    {
        DS_PlayerController->SetUsernameAndPlayerSessionId(Username, PlayerSessionId);
    }
    if (LobbyStatus != EDS_LobbyStatus::SeamlessTraveling)
    {
        AddPlayerInfoToLobbyState(NewPlayerController);
    }
    return InitializedString;
}

void ADS_LobbyGameMode::TryAcceptPlayerSession(const FString& PlayerSessionId, const FString& Username, FString& OutErrorMessage)
{
    if (PlayerSessionId.IsEmpty() || Username.IsEmpty())
    {
        OutErrorMessage = TEXT("Player Session ID and/or Username is invalid.");
        return;
    }

#if WITH_GAMELIFT
    Aws::GameLift::Server::Model::DescribePlayerSessionsRequest Request;
    Request.SetPlayerSessionId(TCHAR_TO_ANSI(*PlayerSessionId));

    const auto& DescribeOutcome = Aws::GameLift::Server::DescribePlayerSessions(Request);
    if (!DescribeOutcome.IsSuccess())
    {
        OutErrorMessage = TEXT("DescribePlayerSessions() failed.");
        return;
    }

    int32 Count = 0;
    const auto* PlayerSessions = DescribeOutcome.GetResult().GetPlayerSessions(Count);
    if (!PlayerSessions || Count == 0)
    {
        OutErrorMessage = TEXT("GetPlayerSessions() returned no results.");
        return;
    }

    for (int32 i = 0; i < Count; i++)
    {
        const auto& Session = PlayerSessions[i];
        if (!Username.Equals(Session.GetPlayerId())) continue;

        if (Session.GetStatus() != Aws::GameLift::Server::Model::PlayerSessionStatus::RESERVED)
        {
            OutErrorMessage = FString::Printf(TEXT("Session for %s is not RESERVED."), *Username);
            return;
        }

        const auto& AcceptOutcome = Aws::GameLift::Server::AcceptPlayerSession(TCHAR_TO_ANSI(*PlayerSessionId));
        if (AcceptOutcome.IsSuccess())
        {
            UE_LOG(LogDedicatedServers, Log, TEXT("AcceptPlayerSession succeeded for %s."), *Username);
            OutErrorMessage = TEXT("");
        }
        else
        {
            const FString SDKError = FString(AcceptOutcome.GetError().GetErrorMessage());
            const FString SDKErrorName = FString(AcceptOutcome.GetError().GetErrorName());
            UE_LOG(LogDedicatedServers, Error, TEXT("AcceptPlayerSession FAILED for %s. Error: [%s] %s"), *Username, *SDKErrorName, *SDKError);
            OutErrorMessage = FString::Printf(TEXT("Failed to accept Player Session for %s."), *Username);
        }
        return;
    }

    OutErrorMessage = FString::Printf(TEXT("No matching session found for %s."), *Username);
#endif
}

void ADS_LobbyGameMode::AddPlayerInfoToLobbyState(AController* Player) const
{
    ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Player);
    ADS_GameState* DS_GameState = GetGameState<ADS_GameState>();
    if (IsValid(DS_GameState) && IsValid(DS_GameState->LobbyState) && IsValid(DS_PlayerController))
    {
        FDS_LobbyPlayerInfo PlayerInfo(DS_PlayerController->PlayerUsername);
        DS_GameState->LobbyState->AddPlayerInfo(PlayerInfo);
    }
}

void ADS_LobbyGameMode::RemovePlayerInfoFromLobbyState(AController* Player) const
{
    ADS_PlayerController* DS_PlayerController = Cast<ADS_PlayerController>(Player);
    ADS_GameState* DS_GameState = GetGameState<ADS_GameState>();
    if (IsValid(DS_GameState) && IsValid(DS_GameState->LobbyState) && IsValid(DS_PlayerController))
    {
        DS_GameState->LobbyState->RemovePlayerInfo(DS_PlayerController->PlayerUsername);
    }
}

void ADS_LobbyGameMode::CheckAndStartLobbyCountdown()
{
    if (GetNumPlayers() >= MinPlayers && LobbyStatus == EDS_LobbyStatus::WaitingForPlayers)
    {
        LobbyStatus = EDS_LobbyStatus::CountdownToSeamlessTravel;
        StartCountdownTimer(LobbyCountdownTimer);
    }
}

void ADS_LobbyGameMode::CheckAndStopLobbyCountdown()
{
    if (GetNumPlayers() -1 < MinPlayers && LobbyStatus == EDS_LobbyStatus::CountdownToSeamlessTravel)
    {
        LobbyStatus = EDS_LobbyStatus::WaitingForPlayers;
        StopCountdownTimer(LobbyCountdownTimer);
    }
}

void ADS_LobbyGameMode::OnCountdownTimerFinished(EDS_CountdownTimerType Type)
{
    Super::OnCountdownTimerFinished(Type);
    if (Type == EDS_CountdownTimerType::LobbyCountdown)
    {
        StopCountdownTimer(LobbyCountdownTimer);
        UE_LOG(LogTemp, Error, TEXT("Lobby counter stopped. Attempting seamless travel."));
        LobbyStatus = EDS_LobbyStatus::SeamlessTraveling;
        TrySeamlessTravel(DestinationMap);
    }
}

void ADS_LobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	/* If you are reading without having experience using GameLift, this
	is a way to have code compiled out unless running on the server. That
	way a client build is not able to run these functions, it would be
	run on the server. */
#if	WITH_GAMELIFT
	InitGameLift(); /* This will be greyed out unless your build target is Development Server */
#endif
}

#if WITH_GAMELIFT
void ADS_LobbyGameMode::InitGameLift()
{
    if (UGameInstance* GameInstance = GetGameInstance(); IsValid(GameInstance))
    {
        if (DS_GameInstanceSubsystem = GameInstance->GetSubsystem<UDS_GameInstanceSubsystem>(); IsValid(DS_GameInstanceSubsystem))
        {
            // Define the Server Params for a GameLift anywhere fleet. These are not needed for a GameLift managed EC2 fleet.
            FServerParameters ServerParametersForAnywhere;

            bool bIsAnywhereActive = false;
            if (FParse::Param(FCommandLine::Get(), TEXT("glAnywhere")))
            {
                bIsAnywhereActive = true;
            }

            if (bIsAnywhereActive)
            {
                SetServerParameters(ServerParametersForAnywhere);
            }

            // Hand over to the Game Instance Subsystem.
            DS_GameInstanceSubsystem->InitGameLift(ServerParametersForAnywhere);
        }
    }
}

void ADS_LobbyGameMode::SetServerParameters(FServerParameters& OutServerParametersForAnywhere)
{
        UE_LOG(LogDedicatedServers, Log, TEXT("Configuring server parameters for Anywhere..."));

        // If GameLift Anywhere is enabled, parse command line arguments and pass them in the ServerParameters object.
        FString glAnywhereWebSocketUrl = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereWebSocketUrl="), glAnywhereWebSocketUrl))
        {
            OutServerParametersForAnywhere.m_webSocketUrl = TCHAR_TO_UTF8(*glAnywhereWebSocketUrl);
        }

        FString glAnywhereFleetId = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereFleetId="), glAnywhereFleetId))
        {
            OutServerParametersForAnywhere.m_fleetId = TCHAR_TO_UTF8(*glAnywhereFleetId);
        }

        FString glAnywhereProcessId = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereProcessId="), glAnywhereProcessId))
        {
            OutServerParametersForAnywhere.m_processId = TCHAR_TO_UTF8(*glAnywhereProcessId);
        }
        else
        {
            // If no ProcessId is passed as a command line argument, generate a randomized unique string.
            FString TimeString = FString::FromInt(std::time(nullptr));
            FString ProcessId = "ProcessId_" + TimeString;
            OutServerParametersForAnywhere.m_processId = TCHAR_TO_UTF8(*ProcessId);
        }

        FString glAnywhereHostId = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereHostId="), glAnywhereHostId))
        {
            OutServerParametersForAnywhere.m_hostId = TCHAR_TO_UTF8(*glAnywhereHostId);
        }

        FString glAnywhereAuthToken = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereAuthToken="), glAnywhereAuthToken))
        {
            OutServerParametersForAnywhere.m_authToken = TCHAR_TO_UTF8(*glAnywhereAuthToken);
        }

        FString glAnywhereAwsRegion = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereAwsRegion="), glAnywhereAwsRegion))
        {
            OutServerParametersForAnywhere.m_awsRegion = TCHAR_TO_UTF8(*glAnywhereAwsRegion);
        }

        FString glAnywhereAccessKey = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereAccessKey="), glAnywhereAccessKey))
        {
            OutServerParametersForAnywhere.m_accessKey = TCHAR_TO_UTF8(*glAnywhereAccessKey);
        }

        FString glAnywhereSecretKey = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereSecretKey="), glAnywhereSecretKey))
        {
            OutServerParametersForAnywhere.m_secretKey = TCHAR_TO_UTF8(*glAnywhereSecretKey);
        }

        FString glAnywhereSessionToken = "";
        if (FParse::Value(FCommandLine::Get(), TEXT("glAnywhereSessionToken="), glAnywhereSessionToken))
        {
            OutServerParametersForAnywhere.m_sessionToken = TCHAR_TO_UTF8(*glAnywhereSessionToken);
        }

        UE_LOG(LogDedicatedServers, SetColor, TEXT("%s"), COLOR_YELLOW);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> WebSocket URL: %s"), *OutServerParametersForAnywhere.m_webSocketUrl);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Fleet ID: %s"), *OutServerParametersForAnywhere.m_fleetId);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Process ID: %s"), *OutServerParametersForAnywhere.m_processId);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Host ID (Compute Name): %s"), *OutServerParametersForAnywhere.m_hostId);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Auth Token: %s"), *OutServerParametersForAnywhere.m_authToken);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Aws Region: %s"), *OutServerParametersForAnywhere.m_awsRegion);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Access Key: %s"), *OutServerParametersForAnywhere.m_accessKey);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Secret Key: %s"), *OutServerParametersForAnywhere.m_secretKey);
        UE_LOG(LogDedicatedServers, Log, TEXT(">>>> Session Token: %s"), *OutServerParametersForAnywhere.m_sessionToken);
        UE_LOG(LogDedicatedServers, SetColor, TEXT("%s"), COLOR_NONE);
}
#endif
#pragma endregion
/*-------------------------------------------------------------------------*/

