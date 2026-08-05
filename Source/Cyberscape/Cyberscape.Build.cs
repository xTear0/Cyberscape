// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cyberscape : ModuleRules
{
	public Cyberscape(ReadOnlyTargetRules Target) : base(Target)
	{
     		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
     	
     		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "PhysicsCore", "DedicatedServers", "GameplayTags", "TechyINV" });
     
     		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "Slate", "SlateCore", "Inventory" });
     
     		// Uncomment if you are using Slate UI
     		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
     		
     		// Uncomment if you are using online features
     		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
     
     		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
     		// Not needed at the moment as no files require this, it is moved to the DedicatedServers Module.
     		if (Target.Type == TargetType.Server)
     		{
     			PublicDependencyModuleNames.Add("GameLiftServerSDK");
     		}
     		else
     		{
     			PublicDefinitions.Add("WITH_GAMELIFT=0");
     		}
     		bEnableExceptions =  true;
     	}
}
