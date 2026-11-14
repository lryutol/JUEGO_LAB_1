// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AventuraUSFX022026L1 : ModuleRules
{
    public AventuraUSFX022026L1(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // FÍJATE QUE AHORA AGREGUÉ "AIModule" AL FINAL
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule" });
    }
}