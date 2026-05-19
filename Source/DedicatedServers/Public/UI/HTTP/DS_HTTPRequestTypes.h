// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "Types/DS_StructTypes.h"
#include "DS_HTTPRequestTypes.generated.h"
/*-------------------------------------------------------------------------*/


/* The IMPLEMENT_DUMPABLE_STRUCT(StructName) macro specifies that this struct
 * will override the virtual const UScriptStruct* GetScriptStruct() const from
 * returning a nullptr to returning the static class, and thus allow the Dump();
 * function to iterate over all of the UPROPERTY() members of the struct and
 * print them to Log. */

// Ensure all structs are initialized to a default value {};
// Refer to the documentation (e.g. https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_SignUp.html)
// if you have any issues. Ensure that you use JavaScript SDK v3.
// All struct property names must match all names from the object it is pulling down, case-sensitive.


/*-------------------------------------------------------------------------*/
/*   Declarations                                                          */
/*-------------------------------------------------------------------------*/

namespace HTTPStatusMessages
{
	extern DEDICATEDSERVERS_API const FString SomethingWentWrong;
}

USTRUCT()
struct FDS_CodeDeliveryDetails : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_CodeDeliveryDetails)
	
	UPROPERTY() FString AttributeName{};
	UPROPERTY() FString DeliveryMedium{};
	UPROPERTY() FString Destination{};
};

USTRUCT()
struct FDS_ChallengeParams : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_ChallengeParams)
	
	UPROPERTY() TMap<FString, FString> Parameters{};
};

USTRUCT()
struct FDS_NewDeviceMetadata : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_NewDeviceMetadata)
	
	UPROPERTY() FString DeviceGroupKey{};
	UPROPERTY() FString DeviceKey{};
};

USTRUCT()
struct FDS_AuthenticationResult : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_AuthenticationResult)

	UPROPERTY() FString AccessToken{};
	UPROPERTY() FString ExpiresIn{};
	UPROPERTY() FString IdToken{};
	UPROPERTY()	FDS_NewDeviceMetadata NewDeviceMetadata{};
	UPROPERTY() FString RefreshToken{};
	UPROPERTY() FString TokenType{};
};

USTRUCT()
struct FDS_MetaData : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_MetaData)

	UPROPERTY() int32 httpStatusCode{};
	UPROPERTY() FString requestId{};
	UPROPERTY() int32 attempts{};
	UPROPERTY() double totalRetryDelay{};
};

USTRUCT()
struct FDS_ListFleetsResponse : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_ListFleetsResponse)

	UPROPERTY() TArray<FString> FleetIds{};
	UPROPERTY() FString NextToken{};
};

USTRUCT()
struct FDS_GameSession : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_GameSession)

	UPROPERTY() FString CreationTime{};
	UPROPERTY() FString CreatorId{};
	UPROPERTY() int32 CurrentPlayerSessionCount{};
	UPROPERTY() FString DnsName{};
	UPROPERTY() FString FleetArn{};
	UPROPERTY() FString FleetId{};
	UPROPERTY() TMap<FString, FString> GameProperties{};
	UPROPERTY() FString GameSessionData{};
	UPROPERTY() FString GameSessionId{};
	UPROPERTY() FString IpAddress{};
	UPROPERTY() FString Location{};
	UPROPERTY() FString MatchmakerData{};
	UPROPERTY() int32 MaximumPlayerSessionCount{};
	UPROPERTY() FString Name{};
	UPROPERTY() FString PlayerSessionCreationPolicy{};
	UPROPERTY() int32 Port{};
	UPROPERTY() FString Status{};
	UPROPERTY() FString StatusReason{};
	UPROPERTY() FString TerminationTime{};
};

USTRUCT()
struct FDS_PlayerSession : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_PlayerSession)

	UPROPERTY() FString PlayerSessionId{};
	UPROPERTY() FString PlayerId{};
	UPROPERTY() FString GameSessionId{};
	UPROPERTY() FString FleetId{};
	UPROPERTY() FString FleetArn{};
	UPROPERTY() FString CreationTime{};
	UPROPERTY() FString TerminationTime{};
	UPROPERTY() FString Status{};
	UPROPERTY() FString IpAddress{};
	UPROPERTY() FString DnsName{};
	UPROPERTY() int32 Port{};
	UPROPERTY() FString PlayerData{};
};

USTRUCT()
struct FDS_SignUpResponse : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_SignUpResponse)

	UPROPERTY() FDS_CodeDeliveryDetails CodeDeliveryDetails{};
	UPROPERTY() bool UserConfirmed{};
	UPROPERTY() FString UserSub{};
};

USTRUCT()
struct FDS_InitiateAuthResponse : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_InitiateAuthResponse)

	UPROPERTY() FDS_AuthenticationResult AuthenticationResult{};	
	UPROPERTY() TArray<FString> AvailableChallenges{};
	UPROPERTY() FString ChallengeName{};
	UPROPERTY() FDS_ChallengeParams ChallengeParameters{};
	UPROPERTY() FString Session{};
	UPROPERTY() FString email{};
};

USTRUCT()
struct FDS_MatchStats : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_MatchStats)
	
	UPROPERTY() int32 kills{};
	UPROPERTY() int32 deaths{};
	UPROPERTY() int32 hits{};
	UPROPERTY() int32 misses{};
	UPROPERTY() int32 headshotKills{};
	UPROPERTY() int32 highestKillStreak{};
	UPROPERTY() int32 revengeKills{};
	UPROPERTY() int32 dethroneKills{};
	UPROPERTY() int32 showstopperKills{};
	UPROPERTY() int32 gotFirstBlood{};
	UPROPERTY() int32 matchWins{};
	UPROPERTY() int32 matchLosses{};
};

USTRUCT()
struct FDS_RecordMatchStatsInput : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_RecordMatchStatsInput)

	UPROPERTY() FDS_MatchStats matchStats{};
	UPROPERTY() FString username{};
};

USTRUCT()
struct FDS_RetrieveMatchStatsResponse : public FDS_DumpableStruct
{
	GENERATED_BODY()
	IMPLEMENT_DUMPABLE_STRUCT(FDS_RetrieveMatchStatsResponse)

	UPROPERTY() int32 kills{};
	UPROPERTY() int32 deaths{};
	UPROPERTY() int32 hits{};
	UPROPERTY() int32 misses{};
	UPROPERTY() int32 headshotKills{};
	UPROPERTY() int32 highestKillStreak{};
	UPROPERTY() int32 revengeKills{};
	UPROPERTY() int32 dethroneKills{};
	UPROPERTY() int32 showstopperKills{};
	UPROPERTY() int32 gotFirstBlood{};
	UPROPERTY() int32 matchWins{};
	UPROPERTY() int32 matchLosses{};
};

/*-------------------------------------------------------------------------*/