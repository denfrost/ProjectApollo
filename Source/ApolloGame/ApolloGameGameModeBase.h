// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"
#include "System/ApolloCoverSystemLibrary.h"

#include "ApolloGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class APOLLOGAME_API AApolloGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AApolloGameGameModeBase();

	virtual void PostLoad() override;

	
	virtual void OnWorldInitDelegate(UWorld* World, const UWorld::InitializationValues IVS);

	// Used to inject our custom navmesh as an actor
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void PreInitializeComponents() override;

	virtual void BeginPlay() override;

	//DEBUG - Display all the cover points on the map
	UFUNCTION(BlueprintCallable)
	void DebugShowCoverPoints();

	//DEBUG - Forces garbage collection
	//Useful for checking if singletons have permanent reference to them
	UFUNCTION(BlueprintCallable)
	void ForceGC();
	
protected:
	//This is stored here to prevent GC from destroying the cover system every so often
	UPROPERTY()
	UApolloCoverSystemLibrary* ApolloCoverSystem;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugDraw = false;

	//Points to the AABB that is used to filter out cover points on map edges
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox MapBounds;

	virtual void PostActorCreated() override;
};
