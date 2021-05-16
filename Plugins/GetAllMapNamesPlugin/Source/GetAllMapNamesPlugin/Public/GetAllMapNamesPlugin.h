// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

#define TIMECLOCK_MODULE_NAME TEXT("JourneyFinder")
DECLARE_LOG_CATEGORY_EXTERN(JourneyFinder, Log, All)

class FGetAllMapNamesPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	//// Registers the plugin's settings as project settings.
	//void RegisterSettings();
};
