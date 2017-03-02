// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class NewFreshStartServerTarget : TargetRules
{
    public NewFreshStartServerTarget(TargetInfo Target)
	{
		Type = TargetType.Server;
        bOutputToEngineBinaries = true;
	}

	//
	// TargetRules interface.
	//
	public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		base.SetupBinaries(Target, ref OutBuildBinaryConfigurations, ref OutExtraModuleNames);
		OutExtraModuleNames.Add("NewFreshStartGame");
	}

	public override void SetupGlobalEnvironment(
        TargetInfo Target,
        ref LinkEnvironmentConfiguration OutLinkEnvironmentConfiguration,
        ref CPPEnvironmentConfiguration OutCPPEnvironmentConfiguration
        )
    {
    }

	public override bool ShouldUseSharedBuildEnvironment(TargetInfo Target)
	{
		return true;
	}

	public override bool GetSupportedPlatforms(ref List<UnrealTargetPlatform> OutPlatforms)
	{
		// It is valid for only server platforms
		return UnrealBuildTool.UnrealBuildTool.GetAllServerPlatforms(ref OutPlatforms, false);
	}
}
