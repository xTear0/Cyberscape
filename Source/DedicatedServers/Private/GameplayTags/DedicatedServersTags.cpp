#include "GameplayTags/DedicatedServersTags.h"

namespace DedicatedServersTags
{
	namespace GameSessionsAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ListFleets, "DedicatedServersTags.GameSessionsAPI.ListFleets",
			"List Fleets resource on the Game Sessions API");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(FindOrCreateGameSession, "DedicatedServersTags.GameSessionsAPI.FindOrCreateGameSession",
			"Retrieves an ACTIVE game session, creating one if one does not exist.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(CreatePlayerSession, "DedicatedServersTags.GameSessionsAPI.CreatePlayerSession",
			"Creates a new Player Session on the GameSessions API.");
	}
	namespace PortalAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignUp, "DedicatedServersTags.PortalAPI.SignUp",
			"Tag associated with Signing Up an account with Cognito from the Portal.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignUpConfirm, "DedicatedServersTags.PortalAPI.SignUpConfirm",
		"Tag associated with confirmation of Signing Up an account with Cognito from the Portal with a MFA code.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignIn, "DedicatedServersTags.PortalAPI.SignIn",
		"Tag associated with signing into your account and getting valid credentials.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(SignOut, "DedicatedServersTags.PortalAPI.SignOut",
		"Tag associated with invalidating the refresh token and signing out.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ResendSignUpConfirm, "DedicatedServersTags.PortalAPI.ResendSignUpConfirm",
		"Tag associated with resending the confirmation of Signing Up an account, requiring a Username.");
	}
	namespace GameStatsAPI
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(RecordMatchStats, "DedicatedServersTags.GameStatsAPI.RecordMatchStats",
    	"Records the stats of a match in GameStatsAPI.");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(RetrieveMatchStats, "DedicatedServersTags.GameStatsAPI.RetrieveMatchStats",
		"Retrieves the stats of player matches in GameStatsAPI.");
	}
}
