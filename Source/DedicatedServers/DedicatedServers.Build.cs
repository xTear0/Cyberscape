using UnrealBuildTool;

public class DedicatedServers : ModuleRules
{
	public DedicatedServers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine", 
			"UMG",
			"GameplayTags",
			"HTTP",
			"NetCore", 
			"ClickyUI"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore",
			"Json",
			"JsonUtilities", 
			"ClickyUI"
		});
		
		if (Target.Type == TargetType.Server)
		{
			PublicDependencyModuleNames.Add("GameLiftServerSDK");
		}
		else
		{
			PublicDefinitions.Add("WITH_GAMELIFT=0");
		}
	}
}
