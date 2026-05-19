// Copyright xTear Studios
/*-------------------------------------------------------------------------*/
#include "Utils/DS_ErrorUtils.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Functions                                                             */
/*-------------------------------------------------------------------------*/
#pragma region DS_ErrorUtils.cpp_Functions

// ============================================================================
//  Internal helper — reads the "name" field from the JSON error body.
// ============================================================================
namespace
{
	FString ExtractExceptionName(const TSharedPtr<FJsonObject>& JsonObject)
	{
		FString ExceptionName;
		if (JsonObject.IsValid() && JsonObject->TryGetStringField(TEXT("name"), ExceptionName))
		{
			return ExceptionName;
		}
		return FString();
	}

	// Fallback used at the end of every API-specific function.
	const FString GenericError = TEXT("Something went wrong. Please try again later.");
}

// ============================================================================
//  Common AWS errors — shared across all API actions.
//  Reference: https://docs.aws.amazon.com/general/latest/gr/common-errors.html
// ============================================================================
bool UDS_ErrorUtils::GetCommonException(const TSharedPtr<FJsonObject>& JsonObject, FString& OutMessage)
{
	const FString Exception = ExtractExceptionName(JsonObject);
	if (Exception.IsEmpty())
	{
		return false;
	}

	// --- AccessDeniedException -------------------------------------------
	// HTTP 400 — caller lacks sufficient IAM permissions.
	if (Exception.Equals(TEXT("AccessDeniedException")))
	{
		OutMessage = TEXT("Access was denied. You don't have permission to do that.");
		return true;
	}

	// --- IncompleteSignature ---------------------------------------------
	// HTTP 400 — request signature does not conform to AWS standards.
	if (Exception.Equals(TEXT("IncompleteSignature")))
	{
		OutMessage = TEXT("The request could not be verified. Please try again.");
		return true;
	}

	// --- InternalFailure -------------------------------------------------
	// HTTP 500 — unknown server-side error or exception.
	if (Exception.Equals(TEXT("InternalFailure")))
	{
		OutMessage = TEXT("An internal server error occurred. Please try again later.");
		return true;
	}

	// --- InvalidAction ---------------------------------------------------
	// HTTP 400 — the requested action or operation is invalid.
	if (Exception.Equals(TEXT("InvalidAction")))
	{
		OutMessage = TEXT("An invalid action was requested. Please contact support.");
		return true;
	}

	// --- InvalidClientTokenId --------------------------------------------
	// HTTP 403 — X.509 certificate or AWS access key ID not found.
	if (Exception.Equals(TEXT("InvalidClientTokenId")))
	{
		OutMessage = TEXT("Authentication credentials are invalid. Please contact support.");
		return true;
	}

	// --- NotAuthorized ---------------------------------------------------
	// HTTP 400 — caller does not have permission to perform this action.
	if (Exception.Equals(TEXT("NotAuthorized")))
	{
		OutMessage = TEXT("You are not authorised to perform this action.");
		return true;
	}

	// --- OptInRequired ---------------------------------------------------
	// HTTP 403 — AWS access key requires a service subscription.
	if (Exception.Equals(TEXT("OptInRequired")))
	{
		OutMessage = TEXT("This service is currently unavailable. Please contact support.");
		return true;
	}

	// --- RequestExpired --------------------------------------------------
	// HTTP 400 — request arrived more than 15 minutes after its timestamp.
	if (Exception.Equals(TEXT("RequestExpired")))
	{
		OutMessage = TEXT("The request expired before it could be processed. Please try again.");
		return true;
	}

	// --- ServiceUnavailable ----------------------------------------------
	// HTTP 503 — temporary server-side failure.
	if (Exception.Equals(TEXT("ServiceUnavailable")))
	{
		OutMessage = TEXT("The service is temporarily unavailable. Please try again shortly.");
		return true;
	}

	// --- ThrottlingException ---------------------------------------------
	// HTTP 400 — request denied due to rate limiting.
	if (Exception.Equals(TEXT("ThrottlingException")))
	{
		OutMessage = TEXT("Too many requests were sent. Please slow down and try again.");
		return true;
	}

	// --- ValidationError -------------------------------------------------
	// HTTP 400 — input does not satisfy AWS service constraints.
	if (Exception.Equals(TEXT("ValidationError")))
	{
		OutMessage = TEXT("Some of the provided information is invalid. Please check your input.");
		return true;
	}

	return false;
}

// ============================================================================
//  SignUp
//  Reference: https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_SignUp.html
// ============================================================================
FString UDS_ErrorUtils::GetSignUpException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);

	// --- CodeDeliveryFailureException ------------------------------------
	// HTTP 400 — verification code could not be delivered to the user.
	if (Exception.Equals(TEXT("CodeDeliveryFailureException")))
	{
		return TEXT("We couldn't send your verification code. Please check your contact details.");
	}

	// --- ForbiddenException ----------------------------------------------
	// HTTP 400 — request blocked by an AWS WAF web ACL on this user pool.
	if (Exception.Equals(TEXT("ForbiddenException")))
	{
		return TEXT("This request was blocked. Please try again or contact support.");
	}

	// --- InternalErrorException ------------------------------------------
	// HTTP 500 — internal Cognito error.
	if (Exception.Equals(TEXT("InternalErrorException")))
	{
		return TEXT("An internal error occurred. Please try again later.");
	}

	// --- InvalidEmailRoleAccessPolicyException ---------------------------
	// HTTP 400 — Cognito isn't permitted to use the configured email identity.
	if (Exception.Equals(TEXT("InvalidEmailRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with email delivery. Please contact support.");
	}

	// --- InvalidLambdaResponseException ----------------------------------
	// HTTP 400 — Cognito received an invalid response from a Lambda trigger.
	if (Exception.Equals(TEXT("InvalidLambdaResponseException")))
	{
		return TEXT("A server-side processing error occurred. Please try again.");
	}

	// --- InvalidParameterException ---------------------------------------
	// HTTP 400 — one or more request parameters are invalid.
	if (Exception.Equals(TEXT("InvalidParameterException")))
	{
		return TEXT("Some of your information is invalid. Please check your details and try again.");
	}

	// --- InvalidPasswordException ----------------------------------------
	// HTTP 400 — password does not meet the user pool's policy requirements.
	if (Exception.Equals(TEXT("InvalidPasswordException")))
	{
		return TEXT("Your password doesn't meet the requirements. Please choose a stronger password.");
	}

	// --- InvalidSmsRoleAccessPolicyException -----------------------------
	// HTTP 400 — the SMS role lacks permission to publish via Amazon SNS.
	if (Exception.Equals(TEXT("InvalidSmsRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- InvalidSmsRoleTrustRelationshipException ------------------------
	// HTTP 400 — the SMS role's trust relationship is invalid for Cognito.
	if (Exception.Equals(TEXT("InvalidSmsRoleTrustRelationshipException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- LimitExceededException ------------------------------------------
	// HTTP 400 — user has exceeded an AWS resource limit.
	if (Exception.Equals(TEXT("LimitExceededException")))
	{
		return TEXT("You have exceeded the allowed limit. Please try again later.");
	}

	// --- NotAuthorizedException ------------------------------------------
	// HTTP 400 — user is not authorized to perform this action.
	if (Exception.Equals(TEXT("NotAuthorizedException")))
	{
		return TEXT("You are not authorised to sign up. Please contact support.");
	}

	// --- ResourceNotFoundException ---------------------------------------
	// HTTP 400 — Cognito cannot find a required resource (e.g. user pool).
	if (Exception.Equals(TEXT("ResourceNotFoundException")))
	{
		return TEXT("A required resource could not be found. Please contact support.");
	}

	// --- TooManyRequestsException ----------------------------------------
	// HTTP 400 — caller has made too many requests in a short period.
	if (Exception.Equals(TEXT("TooManyRequestsException")))
	{
		return TEXT("Too many sign-up attempts. Please wait a moment and try again.");
	}

	// --- UnexpectedLambdaException ---------------------------------------
	// HTTP 400 — Cognito encountered an unexpected error in a Lambda trigger. 
	if (Exception.Equals(TEXT("UnexpectedLambdaException")))
	{
		return TEXT("An unexpected server error occurred. Please try again.");
	}

	// --- UserLambdaValidationException -----------------------------------
	// HTTP 400 — a Lambda trigger raised a user validation error. // Only happens when email exists.
	if (Exception.Equals(TEXT("UserLambdaValidationException")))
	{
		return TEXT("That email is already in use. Please choose a different one.");
	}

	// --- UsernameExistsException -----------------------------------------
	// HTTP 400 — an account with this username already exists in the user pool.
	if (Exception.Equals(TEXT("UsernameExistsException")))
	{
		return TEXT("That username is already taken. Please choose a different one.");
	}
	
	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}

	return GenericError;
}

// ============================================================================
//  ConfirmSignUp
//  Reference: https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_ConfirmSignUp.html
// ============================================================================
FString UDS_ErrorUtils::GetConfirmSignUpException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);

	// --- AliasExistsException --------------------------------------------
	// HTTP 400 — the email or phone number is already an alias for another account.
	if (Exception.Equals(TEXT("AliasExistsException")))
	{
		return TEXT("That email is already linked to another account.");
	}

	// --- CodeMismatchException -------------------------------------------
	// HTTP 400 — the code provided does not match what the server expected.
	if (Exception.Equals(TEXT("CodeMismatchException")))
	{
		return TEXT("The confirmation code is incorrect. Please check it and try again.");
	}

	// --- ExpiredCodeException --------------------------------------------
	// HTTP 400 — the confirmation code has passed its expiry time.
	if (Exception.Equals(TEXT("ExpiredCodeException")))
	{
		return TEXT("Your confirmation code has expired. Please request a new one.");
	}

	// --- ForbiddenException ----------------------------------------------
	// HTTP 400 — request blocked by an AWS WAF web ACL on this user pool.
	if (Exception.Equals(TEXT("ForbiddenException")))
	{
		return TEXT("This request was blocked. Please try again or contact support.");
	}

	// --- InternalErrorException ------------------------------------------
	// HTTP 500 — internal Cognito error.
	if (Exception.Equals(TEXT("InternalErrorException")))
	{
		return TEXT("An internal error occurred. Please try again later.");
	}

	// --- InvalidLambdaResponseException ----------------------------------
	// HTTP 400 — Cognito received an invalid response from a Lambda trigger.
	if (Exception.Equals(TEXT("InvalidLambdaResponseException")))
	{
		return TEXT("A server-side processing error occurred. Please try again.");
	}

	// --- InvalidParameterException ---------------------------------------
	// HTTP 400 — one or more request parameters are invalid.
	if (Exception.Equals(TEXT("InvalidParameterException")))
	{
		return TEXT("Some of your information is invalid. Please check your details and try again.");
	}

	// --- LimitExceededException ------------------------------------------
	// HTTP 400 — user has exceeded an AWS resource limit.
	if (Exception.Equals(TEXT("LimitExceededException")))
	{
		return TEXT("You have exceeded the allowed limit. Please try again later.");
	}

	// --- NotAuthorizedException ------------------------------------------
	// HTTP 400 — user is not authorized to perform this action.
	if (Exception.Equals(TEXT("NotAuthorizedException")))
	{
		return TEXT("You are not authorised to confirm this account. Please contact support.");
	}

	// --- ResourceNotFoundException ---------------------------------------
	// HTTP 400 — Cognito cannot find a required resource (e.g., user pool).
	if (Exception.Equals(TEXT("ResourceNotFoundException")))
	{
		return TEXT("A required resource could not be found. Please contact support.");
	}

	// --- TooManyFailedAttemptsException ----------------------------------
	// HTTP 400 — user has failed this action too many times (e.g., wrong code repeatedly).
	if (Exception.Equals(TEXT("TooManyFailedAttemptsException")))
	{
		return TEXT("Too many failed attempts. Please wait a while before trying again.");
	}

	// --- TooManyRequestsException ----------------------------------------
	// HTTP 400 — caller has made too many requests in a short period.
	if (Exception.Equals(TEXT("TooManyRequestsException")))
	{
		return TEXT("Too many requests were sent. Please wait a moment and try again.");
	}

	// --- UnexpectedLambdaException ---------------------------------------
	// HTTP 400 — Cognito encountered an unexpected error in a Lambda trigger.
	if (Exception.Equals(TEXT("UnexpectedLambdaException")))
	{
		return TEXT("An unexpected server error occurred. Please try again.");
	}

	// --- UserLambdaValidationException -----------------------------------
	// HTTP 400 — a Lambda trigger raised a user validation error.
	if (Exception.Equals(TEXT("UserLambdaValidationException")))
	{
		return TEXT("Your information could not be validated. Please check your details.");
	}

	// --- UserNotFoundException -------------------------------------------
	// HTTP 400 — no account matching the provided username was found.
	if (Exception.Equals(TEXT("UserNotFoundException")))
	{
		return TEXT("No account was found with that username. Please sign up first.");
	}

	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}

	return GenericError;
}

// ============================================================================
//  InitiateAuth
//  Reference: https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_InitiateAuth.html
// ============================================================================
FString UDS_ErrorUtils::GetInitiateAuthException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);

	// --- ForbiddenException ----------------------------------------------
	// HTTP 400 — request blocked by an AWS WAF web ACL on this user pool.
	if (Exception.Equals(TEXT("ForbiddenException")))
	{
		return TEXT("This request was blocked. Please try again or contact support.");
	}

	// --- InternalErrorException ------------------------------------------
	// HTTP 500 — internal Cognito error.
	if (Exception.Equals(TEXT("InternalErrorException")))
	{
		return TEXT("An internal error occurred. Please try again later.");
	}

	// --- InvalidEmailRoleAccessPolicyException ---------------------------
	// HTTP 400 — Cognito isn't permitted to use the configured email identity.
	if (Exception.Equals(TEXT("InvalidEmailRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with email delivery. Please contact support.");
	}

	// --- InvalidLambdaResponseException ----------------------------------
	// HTTP 400 — Cognito received an invalid response from a Lambda trigger.
	if (Exception.Equals(TEXT("InvalidLambdaResponseException")))
	{
		return TEXT("A server-side processing error occurred. Please try again.");
	}

	// --- InvalidParameterException ---------------------------------------
	// HTTP 400 — one or more request parameters are invalid.
	if (Exception.Equals(TEXT("InvalidParameterException")))
	{
		return TEXT("Some of your information is invalid. Please check your details and try again.");
	}

	// --- InvalidSmsRoleAccessPolicyException -----------------------------
	// HTTP 400 — the SMS role lacks permission to publish via Amazon SNS.
	if (Exception.Equals(TEXT("InvalidSmsRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- InvalidSmsRoleTrustRelationshipException ------------------------
	// HTTP 400 — the SMS role's trust relationship is invalid for Cognito.
	if (Exception.Equals(TEXT("InvalidSmsRoleTrustRelationshipException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- InvalidUserPoolConfigurationException ---------------------------
	// HTTP 400 — the user pool configuration is not valid.
	if (Exception.Equals(TEXT("InvalidUserPoolConfigurationException")))
	{
		return TEXT("There is a configuration issue with the user pool. Please contact support.");
	}

	// --- NotAuthorizedException ------------------------------------------
	// HTTP 400 — incorrect username or password.
	if (Exception.Equals(TEXT("NotAuthorizedException")))
	{
		return TEXT("Incorrect username or password.");
	}

	// --- PasswordResetRequiredException ----------------------------------
	// HTTP 400 — the user must reset their password before signing in.
	if (Exception.Equals(TEXT("PasswordResetRequiredException")))
	{
		return TEXT("You must reset your password before signing in.");
	}

	// --- ResourceNotFoundException ---------------------------------------
	// HTTP 400 — Cognito cannot find a required resource (e.g. user pool).
	if (Exception.Equals(TEXT("ResourceNotFoundException")))
	{
		return TEXT("A required resource could not be found. Please contact support.");
	}

	// --- TooManyRequestsException ----------------------------------------
	// HTTP 400 — caller has made too many requests in a short period.
	if (Exception.Equals(TEXT("TooManyRequestsException")))
	{
		return TEXT("Too many sign-in attempts. Please wait a moment and try again.");
	}

	// --- UnexpectedLambdaException ---------------------------------------
	// HTTP 400 — Cognito encountered an unexpected error in a Lambda trigger.
	if (Exception.Equals(TEXT("UnexpectedLambdaException")))
	{
		return TEXT("An unexpected server error occurred. Please try again.");
	}

	// --- UnsupportedOperationException -----------------------------------
	// HTTP 400 — the operation is not enabled for this user pool client.
	if (Exception.Equals(TEXT("UnsupportedOperationException")))
	{
		return TEXT("This sign-in method is not supported. Please contact support.");
	}

	// --- UserLambdaValidationException -----------------------------------
	// HTTP 400 — a Lambda trigger raised a user validation error.
	if (Exception.Equals(TEXT("UserLambdaValidationException")))
	{
		return TEXT("Your information could not be validated. Please check your details.");
	}

	// --- UserNotConfirmedException ---------------------------------------
	// HTTP 400 — the user has not completed the account confirmation step.
	if (Exception.Equals(TEXT("UserNotConfirmedException")))
	{
		return TEXT("Your account has not been confirmed yet. Please check your email for a confirmation code.");
	}

	// --- UserNotFoundException -------------------------------------------
	// HTTP 400 — no account matching the provided username was found.
	if (Exception.Equals(TEXT("UserNotFoundException")))
	{
		return TEXT("No account was found with that username.");
	}

	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}

	return GenericError;
}


// ============================================================================
//  ResendConfirmationCode
//  Reference: https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_ResendConfirmationCode.html
// ============================================================================
FString UDS_ErrorUtils::GetResendConfirmationCodeException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);

	// --- CodeDeliveryFailureException ------------------------------------
	// HTTP 400 — verification code could not be delivered to the user.
	if (Exception.Equals(TEXT("CodeDeliveryFailureException")))
	{
		return TEXT("We couldn't send your confirmation code. Please check your contact details.");
	}

	// --- ForbiddenException ----------------------------------------------
	// HTTP 400 — request blocked by an AWS WAF web ACL on this user pool.
	if (Exception.Equals(TEXT("ForbiddenException")))
	{
		return TEXT("This request was blocked. Please try again or contact support.");
	}

	// --- InternalErrorException ------------------------------------------
	// HTTP 500 — internal Cognito error.
	if (Exception.Equals(TEXT("InternalErrorException")))
	{
		return TEXT("An internal error occurred. Please try again later.");
	}

	// --- InvalidEmailRoleAccessPolicyException ---------------------------
	// HTTP 400 — Cognito isn't permitted to use the configured email identity.
	if (Exception.Equals(TEXT("InvalidEmailRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with email delivery. Please contact support.");
	}

	// --- InvalidLambdaResponseException ----------------------------------
	// HTTP 400 — Cognito received an invalid response from a Lambda trigger.
	if (Exception.Equals(TEXT("InvalidLambdaResponseException")))
	{
		return TEXT("A server-side processing error occurred. Please try again.");
	}

	// --- InvalidParameterException ---------------------------------------
	// HTTP 400 — one or more request parameters are invalid.
	if (Exception.Equals(TEXT("InvalidParameterException")))
	{
		return TEXT("Some of your information is invalid. Please check your details and try again.");
	}

	// --- InvalidSmsRoleAccessPolicyException -----------------------------
	// HTTP 400 — the SMS role lacks permission to publish via Amazon SNS.
	if (Exception.Equals(TEXT("InvalidSmsRoleAccessPolicyException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- InvalidSmsRoleTrustRelationshipException ------------------------
	// HTTP 400 — the SMS role's trust relationship is invalid for Cognito.
	if (Exception.Equals(TEXT("InvalidSmsRoleTrustRelationshipException")))
	{
		return TEXT("There is a configuration issue with SMS delivery. Please contact support.");
	}

	// --- LimitExceededException ------------------------------------------
	// HTTP 400 — user has exceeded an AWS resource limit.
	if (Exception.Equals(TEXT("LimitExceededException")))
	{
		return TEXT("You have exceeded the allowed limit. Please try again later.");
	}

	// --- NotAuthorizedException ------------------------------------------
	// HTTP 400 — user is not authorised to perform this action.
	if (Exception.Equals(TEXT("NotAuthorizedException")))
	{
		return TEXT("You are not authorised to request a new code. Please contact support.");
	}

	// --- ResourceNotFoundException ---------------------------------------
	// HTTP 400 — Cognito cannot find a required resource (e.g. user pool).
	if (Exception.Equals(TEXT("ResourceNotFoundException")))
	{
		return TEXT("A required resource could not be found. Please contact support.");
	}

	// --- TooManyRequestsException ----------------------------------------
	// HTTP 400 — caller has made too many requests in a short period.
	if (Exception.Equals(TEXT("TooManyRequestsException")))
	{
		return TEXT("Too many requests were sent. Please wait a moment before trying again.");
	}

	// --- UnexpectedLambdaException ---------------------------------------
	// HTTP 400 — Cognito encountered an unexpected error in a Lambda trigger.
	if (Exception.Equals(TEXT("UnexpectedLambdaException")))
	{
		return TEXT("An unexpected server error occurred. Please try again.");
	}

	// --- UserLambdaValidationException -----------------------------------
	// HTTP 400 — a Lambda trigger raised a user validation error.
	if (Exception.Equals(TEXT("UserLambdaValidationException")))
	{
		return TEXT("Your information could not be validated. Please check your details.");
	}

	// --- UserNotFoundException -------------------------------------------
	// HTTP 400 — no account matching the provided username was found.
	if (Exception.Equals(TEXT("UserNotFoundException")))
	{
		return TEXT("No account was found with that username. Please sign up first.");
	}

	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}

	return GenericError;
}

// ============================================================================
//  GlobalSignOut
//  Reference: https://docs.aws.amazon.com/cognito-user-identity-pools/latest/APIReference/API_GlobalSignOut.html
// ============================================================================
FString UDS_ErrorUtils::GetGlobalSignOutException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);
 
	// --- ForbiddenException ----------------------------------------------
	// HTTP 400 (client) — request blocked by an AWS WAF web ACL on this user pool.
	if (Exception.Equals(TEXT("ForbiddenException")))
	{
		return TEXT("This request was blocked. Please try again or contact support.");
	}
 
	// --- InternalErrorException ------------------------------------------
	// HTTP 500 (server) — internal Cognito error.
	if (Exception.Equals(TEXT("InternalErrorException")))
	{
		return TEXT("An internal error occurred. Please try again later.");
	}
 
	// --- InvalidParameterException ---------------------------------------
	// HTTP 400 (client) — one or more request parameters are invalid.
	if (Exception.Equals(TEXT("InvalidParameterException")))
	{
		return TEXT("Some of your information is invalid. Please check your details and try again.");
	}
 
	// --- NotAuthorizedException ------------------------------------------
	// HTTP 400 (client) — the access token is invalid or the user is not authorised.
	if (Exception.Equals(TEXT("NotAuthorizedException")))
	{
		return TEXT("You are not authorized to sign out. Your session may have already expired.");
	}
 
	// --- PasswordResetRequiredException ----------------------------------
	// HTTP 400 (client) — the user must reset their password before continuing.
	if (Exception.Equals(TEXT("PasswordResetRequiredException")))
	{
		return TEXT("You must reset your password before continuing.");
	}
 
	// --- ResourceNotFoundException ---------------------------------------
	// HTTP 400 (client) — Cognito cannot find a required resource (e.g. user pool).
	if (Exception.Equals(TEXT("ResourceNotFoundException")))
	{
		return TEXT("A required resource could not be found. Please contact support.");
	}
 
	// --- TooManyRequestsException ----------------------------------------
	// HTTP 400 (client) — caller has made too many requests in a short period.
	if (Exception.Equals(TEXT("TooManyRequestsException")))
	{
		return TEXT("Too many requests were sent. Please wait a moment before trying again.");
	}
 
	// --- UserNotConfirmedException ---------------------------------------
	// HTTP 400 (client) — the user has not completed the account confirmation step.
	if (Exception.Equals(TEXT("UserNotConfirmedException")))
	{
		return TEXT("Your account has not been confirmed yet. Please check your email for a confirmation code.");
	}
 
	// --- CognitoIdentityProviderServiceException -------------------------
	// Base exception for all CognitoIdentityProvider service exceptions.
	// Caught as a last resort before the generic fallback.
	if (Exception.Equals(TEXT("CognitoIdentityProviderServiceException")))
	{
		return TEXT("A sign-out error occurred. Please try again or contact support.");
	}
 
	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}
 
	return GenericError;
}

// ============================================================================
//  CreateGameSession (FindOrCreate)
//  Reference: https://docs.aws.amazon.com/AWSJavaScriptSDK/v3/latest/client/gamelift/command/CreateGameSessionCommand/
// ============================================================================
FString UDS_ErrorUtils::GetFindOrCreateGameSessionResponseException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);
 
	// --- ConflictException -----------------------------------------------
	// client — the operation conflicts with the current state of a service resource.
	if (Exception.Equals(TEXT("ConflictException")))
	{
		return TEXT("A session conflict occurred. Please try again.");
	}
 
	// --- FleetCapacityExceededException ----------------------------------
	// client — the fleet has no available instances to fulfil the request.
	if (Exception.Equals(TEXT("FleetCapacityExceededException")))
	{
		return TEXT("All servers are currently full. Please try again in a moment.");
	}
 
	// --- IdempotentParameterMismatchException ----------------------------
	// client — a game session with this custom ID already exists in this fleet.
	if (Exception.Equals(TEXT("IdempotentParameterMismatchException")))
	{
		return TEXT("A session with that ID already exists. Please try again.");
	}
 
	// --- InternalServiceException ----------------------------------------
	// server — unrecoverable internal failure while processing the request.
	if (Exception.Equals(TEXT("InternalServiceException")))
	{
		return TEXT("An internal server error occurred. Please try again later.");
	}
 
	// --- InvalidFleetStatusException -------------------------------------
	// client — the operation conflicts with the current state of the fleet.
	if (Exception.Equals(TEXT("InvalidFleetStatusException")))
	{
		return TEXT("The game server fleet is not ready. Please try again shortly.");
	}
 
	// --- InvalidRequestException -----------------------------------------
	// client — one or more parameter values in the request are invalid.
	if (Exception.Equals(TEXT("InvalidRequestException")))
	{
		return TEXT("The matchmaking request was invalid. Please try again.");
	}
 
	// --- LimitExceededException ------------------------------------------
	// client — the operation would cause the resource to exceed its service limit.
	if (Exception.Equals(TEXT("LimitExceededException")))
	{
		return TEXT("The session limit has been reached. Please try again later.");
	}
 
	// --- NotFoundException -----------------------------------------------
	// client — the requested resource was not found or not yet created.
	if (Exception.Equals(TEXT("NotFoundException")))
	{
		return TEXT("The game session could not be found. Please try again.");
	}
 
	// --- TerminalRoutingStrategyException --------------------------------
	// client — the alias has a terminal routing strategy and cannot be resolved.
	if (Exception.Equals(TEXT("TerminalRoutingStrategyException")))
	{
		return TEXT("This server region is currently unavailable. Please contact support.");
	}
 
	// --- UnauthorizedException -------------------------------------------
	// client — the client failed authentication and should not retry.
	if (Exception.Equals(TEXT("UnauthorizedException")))
	{
		return TEXT("Authentication failed. Please sign in again.");
	}
 
	// --- UnsupportedRegionException --------------------------------------
	// client — the requested operation is not supported in this region.
	if (Exception.Equals(TEXT("UnsupportedRegionException")))
	{
		return TEXT("Game sessions are not available in your region. Please contact support.");
	}
 
	// --- GameLiftServiceException ----------------------------------------
	// Base exception class for all GameLift service exceptions.
	// Caught as a last resort before the generic fallback.
	if (Exception.Equals(TEXT("GameLiftServiceException")))
	{
		return TEXT("A matchmaking error occurred. Please try again or contact support.");
	}
 
	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}
 
	return GenericError;
}
 
// ============================================================================
//  CreatePlayerSession
//  Reference: https://docs.aws.amazon.com/gameliftservers/latest/apireference/API_CreatePlayerSession.html
// ============================================================================
FString UDS_ErrorUtils::GetCreatePlayerResponseException(const TSharedPtr<FJsonObject>& JsonObject)
{
	const FString Exception = ExtractExceptionName(JsonObject);
 
	// --- GameSessionFullException ----------------------------------------
	// HTTP 400 — the game instance is full and cannot accept more players.
	if (Exception.Equals(TEXT("GameSessionFullException")))
	{
		return TEXT("This session is full. Please try joining a different one.");
	}
 
	// --- InternalServiceException ----------------------------------------
	// HTTP 500 — unrecoverable internal failure while processing the request.
	if (Exception.Equals(TEXT("InternalServiceException")))
	{
		return TEXT("An internal server error occurred. Please try again later.");
	}
 
	// --- InvalidGameSessionStatusException -------------------------------
	// HTTP 400 — the operation conflicts with the current state of the game session.
	if (Exception.Equals(TEXT("InvalidGameSessionStatusException")))
	{
		return TEXT("The game session is no longer available to join. Please try again.");
	}
 
	// --- InvalidRequestException -----------------------------------------
	// HTTP 400 — one or more parameter values in the request are invalid.
	if (Exception.Equals(TEXT("InvalidRequestException")))
	{
		return TEXT("The join request was invalid. Please try again.");
	}
 
	// --- NotFoundException -----------------------------------------------
	// HTTP 400 — the requested resource was not found or not yet created.
	if (Exception.Equals(TEXT("NotFoundException")))
	{
		return TEXT("The game session could not be found. Please try again.");
	}
 
	// --- TerminalRoutingStrategyException --------------------------------
	// HTTP 400 — the alias has a terminal routing strategy and cannot be resolved.
	if (Exception.Equals(TEXT("TerminalRoutingStrategyException")))
	{
		return TEXT("This server region is currently unavailable. Please contact support.");
	}
 
	// --- UnauthorizedException -------------------------------------------
	// HTTP 400 — the client failed authentication and should not retry.
	if (Exception.Equals(TEXT("UnauthorizedException")))
	{
		return TEXT("Authentication failed. Please sign in again.");
	}
 
	// --- Common AWS errors (fallthrough) ---------------------------------
	FString CommonMessage;
	if (GetCommonException(JsonObject, CommonMessage))
	{
		return CommonMessage;
	}
 
	return GenericError;
}
#pragma endregion
/*-------------------------------------------------------------------------*/