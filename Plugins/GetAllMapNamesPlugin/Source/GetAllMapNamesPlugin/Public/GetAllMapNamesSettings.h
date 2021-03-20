// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "GetAllMapNamesSettings.generated.h"

/**
 * 
 */
UCLASS(config = JourneyFinder, defaultconfig)
class GETALLMAPNAMESPLUGIN_API UGetAllMapNamesSettings : public UObject
{
	GENERATED_BODY()

		UGetAllMapNamesSettings();

public:
		//List of Map Category (Campaign, Deathmatch, CTF, etc) and the location
		UPROPERTY(EditAnywhere, config, Category = Maps)
		TMap<int32, FString> GameMaps;
	
};
