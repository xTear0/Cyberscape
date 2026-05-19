using UnrealBuildTool;
using System.Collections.Generic;

public class CyberscapeClientTarget : TargetRules
{
	public CyberscapeClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;

		DefaultBuildSettings = BuildSettingsVersion.V6;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;

		ExtraModuleNames.Add("Cyberscape");
		ExtraModuleNames.Add("DedicatedServers");
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider()
	{
		ExtraModuleNames.AddRange(new string[] { "System7" });
	}
}