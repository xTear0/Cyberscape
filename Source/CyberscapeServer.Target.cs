using UnrealBuildTool;
using System.Collections.Generic;

public class CyberscapeServerTarget : TargetRules
{
    public CyberscapeServerTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Server;

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
