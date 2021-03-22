// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GetAllMapNamesSettings.h"
#include "GetAllMapNamesPluginBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UGetAllMapNamesPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	

		UFUNCTION(BlueprintPure, meta = (DisplayName = "GetAllMapNames", Keywords = "GAMNMaps"), Category = "MapNames")
		static FORCEINLINE TArray<FString> GetAllMapNames_p()
	{
		TArray<FString> MapFiles;
		
		IFileManager::Get().FindFilesRecursive(MapFiles, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

		for (int32 i = 0; i < MapFiles.Num(); i++)
		{
			//replace the whole directory string with only the name of the map

			int32 lastSlashIndex = -1;
			if (MapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureMapName;

				//length - 5 because of the ".umap" suffix
				for (int32 j = lastSlashIndex + 1; j < MapFiles[i].Len() - 5; j++)
				{
					pureMapName.AppendChar(MapFiles[i][j]);
				}

				MapFiles[i] = pureMapName;
			}
		}

		return MapFiles;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAllMapNames", Keywords = "GAMNMaps"), Category = "MapNames")
		static FORCEINLINE TArray<FString> GetAllMapNames()
	{
		TArray<FString> MapFiles;

		IFileManager::Get().FindFilesRecursive(MapFiles, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

		for (int32 i = 0; i < MapFiles.Num(); i++)
		{
			//replace the whole directory string with only the name of the map

			int32 lastSlashIndex = -1;
			if (MapFiles[i].FindLastChar('/', lastSlashIndex))
			{
				FString pureMapName;

				//length - 5 because of the ".umap" suffix
				for (int32 j = lastSlashIndex + 1; j < MapFiles[i].Len() - 5; j++)
				{
					pureMapName.AppendChar(MapFiles[i][j]);
				}

				MapFiles[i] = pureMapName;
			}
		}

		return MapFiles;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAllMapNames_ByFolder", Keywords = "GAMNMapsFolder"), Category = "MapNames")
	static TArray<FString> GetAllMapNames_ByFolder(FString levelsFolder)
	{
		TArray<FString> MapPaths;
		IFileManager::Get().FindFilesRecursive(MapPaths, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false, false);

		TArray<FString> MapNames = TArray<FString>();

		for (FString mapPath : MapPaths)
		{
			//remove the path
			FString mapFile;
			FString discard;
			mapPath.Split(levelsFolder, &discard, &mapFile);

			//remove the extension
			FString mapName;
			if (mapFile.Split(".", &mapName, &discard))
			{
				//add map name to our array
				MapNames.Add(mapName);
			}
		}
		return MapNames;
	}

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "GetAllMapNames_ByDLCFolder", Keywords = "DLCGAMN"), Category = "MapNames")
		static TArray<FString> GetAllDLCMapNames_ByFolder(FString levelsFolder)
	{
		TArray<FString> MapPaths;
		IFileManager::Get().FindFilesRecursive(MapPaths, *FPaths::ProjectPluginsDir(), TEXT("*.umap"), true, false, false);

		TArray<FString> MapNames = TArray<FString>();

		for (FString mapPath : MapPaths)
		{
			//remove the path
			FString mapFile;
			FString discard;
			mapPath.Split(levelsFolder, &discard, &mapFile);

			//remove the extension
			FString mapName;
			if (mapFile.Split(".", &mapName, &discard))
			{
				//add map name to our array
				MapNames.Add(mapName);
			}
		}
		return MapNames;
	}

	
};
