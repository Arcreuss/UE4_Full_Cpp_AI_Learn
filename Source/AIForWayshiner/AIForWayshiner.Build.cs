// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using UnrealBuildTool;

public class AIForWayshiner : ModuleRules
{
	public AIForWayshiner(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"AIModule",
			"GameplayTasks",
			"NavigationSystem"
		});
	}
}
