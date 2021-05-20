// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

using UnrealBuildTool;
using System.Collections.Generic;

public class ApolloGameTarget : TargetRules
{
	public ApolloGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bUsesSteam = true;
		ExtraModuleNames.AddRange( new string[] { "ApolloGame" } );
	}
}
