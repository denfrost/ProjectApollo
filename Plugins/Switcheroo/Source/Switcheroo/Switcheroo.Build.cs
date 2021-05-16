// Copyright 2018-2020 Francesco Camarlinghi. All rights reserved.

using UnrealBuildTool;

public class Switcheroo : ModuleRules
{
	public Switcheroo(ReadOnlyTargetRules Target)
		 : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bLegacyPublicIncludePaths = false;

		PrivateIncludePaths.Add("Switcheroo/Private");

		PrivateDependencyModuleNames.AddRange(new string[] {
			"SlateCore",
			"Slate",
			"InputCore",
		});

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
#if UE_4_26_OR_LATER
			"DeveloperSettings",
#endif
			"Engine",
		});
	}
}
