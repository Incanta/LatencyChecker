
// Copyright Incanta Games. All Rights Reserved.

using UnrealBuildTool;

public class LatencyChecker : ModuleRules {
  public LatencyChecker(ReadOnlyTargetRules Target) : base(Target) {
    PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

    PublicIncludePaths.AddRange(
      new string[] {
      }
      );


    PrivateIncludePaths.AddRange(
      new string[] {
      }
      );


    PublicDependencyModuleNames.AddRange(
      new string[]
      {
        "Core",
      }
      );


    PrivateDependencyModuleNames.AddRange(
      new string[]
      {
        "CoreUObject",
        "Engine",
        "Slate",
        "SlateCore",
        "Icmp",
        "HTTP",
        "WebSockets",
      }
      );


    DynamicallyLoadedModuleNames.AddRange(
      new string[]
      {
      }
      );
  }
}