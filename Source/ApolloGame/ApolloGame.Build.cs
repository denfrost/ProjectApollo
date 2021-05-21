// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

using UnrealBuildTool;

public class ApolloGame : ModuleRules
{
	public ApolloGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "Engine", "InputCore", "AIModule", "GameplayTasks", "UMG", "RHI", "RenderCore", "CoreUObject" });

		PublicDependencyModuleNames.AddRange(new string[] { "UINavigation", "AsyncLoadingScreen" });
		PrivateDependencyModuleNames.AddRange(new string[] { "BYGRichText" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		PrivateDependencyModuleNames.Add("OnlineSubsystem");

		  // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
