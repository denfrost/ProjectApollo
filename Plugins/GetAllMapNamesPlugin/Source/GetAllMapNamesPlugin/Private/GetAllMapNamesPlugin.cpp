// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GetAllMapNamesPlugin.h"
#include "ISettingsModule.h"
#include "GetAllMapNamesSettings.h"

#define LOCTEXT_NAMESPACE "FGetAllMapNamesPluginModule"

void FGetAllMapNamesPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	RegisterSettings();
}

void FGetAllMapNamesPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}

void FGetAllMapNamesPluginModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Journey Finder", LOCTEXT("RuntimeSettingsName", "Journey Finder"), LOCTEXT("RuntimeSettingsDescription", "Configure the Journey Finder settings"), GetMutableDefault<UGetAllMapNamesSettings>());

	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGetAllMapNamesPluginModule, GetAllMapNamesPlugin)