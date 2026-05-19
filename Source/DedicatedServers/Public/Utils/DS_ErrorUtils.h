// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#pragma once
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DS_ErrorUtils.generated.h"
/*-------------------------------------------------------------------------*/



/**
 * DS_ErrorUtils
 * 
 * A Blueprint Function Library for parsing AWS Cognito error responses into
 * human-readable status messages. Each function targets a specific Cognito
 * API action so that errors with the same name but different contexts can
 * be handled distinctly in the future.
 * 
 * JSON field expected: "name" (the exception type string)
 * 
 * Usage:
 *   FString Msg = UDS_ErrorUtils::GetSignUpException(JsonObject);
 *   FString Msg = UDS_ErrorUtils::GetConfirmSignUpException(JsonObject);
 */


/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region DS_ErrorUtils.h_Class
UCLASS()
class DEDICATEDSERVERS_API UDS_ErrorUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Parses common AWS-wide errors shared across all API actions.
	 * Returns an empty string if the exception name is not a known common error.
	 * Call this as a fallback inside the API-specific functions below.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @param OutMessage  The human-readable message if a match was found.
	 * @return            True if a known common error was matched.
	 */
	static bool GetCommonException(const TSharedPtr<FJsonObject>& JsonObject, FString& OutMessage);

	// -------------------------------------------------------------------------
	// SignUp — POST /  Action: SignUp
	// https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_SignUp.html
	// -------------------------------------------------------------------------

	/**
	 * Parses a Cognito SignUp error response and returns a short, user-facing
	 * message explaining what went wrong.
	 *
	 * Handled errors:
	 *   CodeDeliveryFailureException, ForbiddenException, InternalErrorException,
	 *   InvalidEmailRoleAccessPolicyException, InvalidLambdaResponseException,
	 *   InvalidParameterException, InvalidPasswordException,
	 *   InvalidSmsRoleAccessPolicyException, InvalidSmsRoleTrustRelationshipException,
	 *   LimitExceededException, NotAuthorizedException, ResourceNotFoundException,
	 *   TooManyRequestsException, UnexpectedLambdaException,
	 *   UserLambdaValidationException, UsernameExistsException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetSignUpException(const TSharedPtr<FJsonObject>& JsonObject);

	// -------------------------------------------------------------------------
	// ConfirmSignUp — POST /  Action: ConfirmSignUp
	// https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_ConfirmSignUp.html
	// -------------------------------------------------------------------------

	/**
	 * Parses a Cognito ConfirmSignUp error response and returns a short,
	 * user-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   AliasExistsException, CodeMismatchException, ExpiredCodeException,
	 *   ForbiddenException, InternalErrorException, InvalidLambdaResponseException,
	 *   InvalidParameterException, LimitExceededException, NotAuthorizedException,
	 *   ResourceNotFoundException, TooManyFailedAttemptsException,
	 *   TooManyRequestsException, UnexpectedLambdaException,
	 *   UserLambdaValidationException, UserNotFoundException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognized.
	 */
	static FString GetConfirmSignUpException(const TSharedPtr<FJsonObject>& JsonObject);

	// -------------------------------------------------------------------------
	// InitiateAuth — POST /  Action: InitiateAuth
	// https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_InitiateAuth.html
	// -------------------------------------------------------------------------

	/**
	 * Parses a Cognito InitiateAuth error response and returns a short,
	 * user-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   ForbiddenException, InternalErrorException,
	 *   InvalidEmailRoleAccessPolicyException, InvalidLambdaResponseException,
	 *   InvalidParameterException, InvalidSmsRoleAccessPolicyException,
	 *   InvalidSmsRoleTrustRelationshipException, InvalidUserPoolConfigurationException,
	 *   NotAuthorizedException, PasswordResetRequiredException,
	 *   ResourceNotFoundException, TooManyRequestsException,
	 *   UnexpectedLambdaException, UnsupportedOperationException,
	 *   UserLambdaValidationException, UserNotConfirmedException, UserNotFoundException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetInitiateAuthException(const TSharedPtr<FJsonObject>& JsonObject);

	// -------------------------------------------------------------------------
	// ResendConfirmationCode — POST /  Action: ResendConfirmationCode
	// https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_ResendConfirmationCode.html
	// -------------------------------------------------------------------------

	/**
	 * Parses a Cognito ResendConfirmationCode error response and returns a short,
	 * user-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   CodeDeliveryFailureException, ForbiddenException, InternalErrorException,
	 *   InvalidEmailRoleAccessPolicyException, InvalidLambdaResponseException,
	 *   InvalidParameterException, InvalidSmsRoleAccessPolicyException,
	 *   InvalidSmsRoleTrustRelationshipException, LimitExceededException,
	 *   NotAuthorizedException, ResourceNotFoundException,
	 *   TooManyRequestsException, UnexpectedLambdaException,
	 *   UserLambdaValidationException, UserNotFoundException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetResendConfirmationCodeException(const TSharedPtr<FJsonObject>& JsonObject);
	
	// -------------------------------------------------------------------------
	// GlobalSignOut — POST /  Action: GlobalSignOut
	// https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_GlobalSignOut.html
	// -------------------------------------------------------------------------
 
	/**
	 * Parses a Cognito GlobalSignOut error response and returns a short,
	 * user`-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   ForbiddenException, InternalErrorException, InvalidParameterException,
	 *   NotAuthorizedException, PasswordResetRequiredException,
	 *   ResourceNotFoundException, TooManyRequestsException,
	 *   UserNotConfirmedException, CognitoIdentityProviderServiceException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetGlobalSignOutException(const TSharedPtr<FJsonObject>& JsonObject);

	// -------------------------------------------------------------------------
	// CreateGameSession — GameLift
	// https://docs.aws.amazon.com/AWSJavaScriptSDK/v3/latest/client/gamelift/command/CreateGameSessionCommand/
	// -------------------------------------------------------------------------
 
	/**
	 * Parses a GameLift CreateGameSession error response and returns a short,
	 * user-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   ConflictException, FleetCapacityExceededException,
	 *   IdempotentParameterMismatchException, InternalServiceException,
	 *   InvalidFleetStatusException, InvalidRequestException,
	 *   LimitExceededException, NotFoundException,
	 *   TerminalRoutingStrategyException, UnauthorizedException,
	 *   UnsupportedRegionException, GameLiftServiceException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetFindOrCreateGameSessionResponseException(const TSharedPtr<FJsonObject>& JsonObject);
 
	// -------------------------------------------------------------------------
	// CreatePlayerSession — GameLift
	// https://docs.aws.amazon.com/gameliftservers/latest/apireference/API_CreatePlayerSession.html
	// -------------------------------------------------------------------------
 
	/**
	 * Parses a GameLift CreatePlayerSession error response and returns a short,
	 * user-facing message explaining what went wrong.
	 *
	 * Handled errors:
	 *   GameSessionFullException, InternalServiceException,
	 *   InvalidGameSessionStatusException, InvalidRequestException,
	 *   NotFoundException, TerminalRoutingStrategyException,
	 *   UnauthorizedException
	 *   + all common AWS errors.
	 *
	 * @param JsonObject  The deserialized error JSON response body.
	 * @return            A short human-readable error message.
	 *                    Falls back to a generic message if unrecognised.
	 */
	static FString GetCreatePlayerResponseException(const TSharedPtr<FJsonObject>& JsonObject);
};
#pragma endregion
/*-------------------------------------------------------------------------*/
