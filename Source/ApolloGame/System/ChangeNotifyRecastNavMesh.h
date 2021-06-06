// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "NavMesh/RecastNavMesh.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ChangeNotifyRecastNavMesh.generated.h"


// DELEGATES //

// Fired every X seconds.
// ChangedTiles contains tiles that have been updated since the last timer.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavmeshTilesUpdatedBufferedDelegate, const TSet<uint32>&, ChangedTiles);

// Fired as tiles are updated.
// ChangedTiles contains the same tiles as what get passed around inside Recast.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavmeshTilesUpdatedImmediateDelegate, const TSet<uint32>&, ChangedTiles);

// Fires once navigation generation is finished, i.e. there are no dirty tiles left.
// ChangedTiles contains all the tiles that have been updated since the last time nav was finished.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNavmeshTilesUpdatedUntilFinishedDelegate, const TSet<uint32>&, ChangedTiles);

/**
* Subclass of ARecastNavMesh that notifies listeners of Recast's tile updates via a custom delegate.
*/
UCLASS()
class APOLLOGAME_API AChangeNotifyRecastNavMesh : public ARecastNavMesh
{
	GENERATED_BODY()

protected:
	
	TSet<uint32> UpdatedTilesIntervalBuffer;
	TSet<uint32> UpdatedTilesUntilFinishedBuffer;

	//Lock used for interval buffered tile updates
	FCriticalSection TileUpdateLockObject;

	//How often should the NavMesh Tiles be updated/refreshed
	const float TileBufferInterval = 0.2f;

	//Timer that controls how often tiles are updated
	FTimerHandle TileUpdateTimerHandle;

public:
	
	//Overriding base class Event Dispatchers
	UPROPERTY()
	FNavmeshTilesUpdatedImmediateDelegate NavMeshTilesUpdatedImmediateDelegate;

	UPROPERTY()
	FNavmeshTilesUpdatedBufferedDelegate NavMeshTilesUpdatedBufferedDelegate;
	
	UPROPERTY()
	FNavmeshTilesUpdatedUntilFinishedDelegate NavMeshTilesUpdatedUntilFinishedDelegate;

	//Constructor
	AChangeNotifyRecastNavMesh();

	AChangeNotifyRecastNavMesh(const FObjectInitializer& ObjectInitializer);

	//Called when the world is created, basically when gameplay starts
	virtual void BeginPlay() override;

	//Called when the world is being destroyed, when gameplay ends
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//Called after a set of tiles has been updated. Due to how the base class is implemented, the same tiles may be contained after this function is successful
	//We get around this by buffering tile updates, see above Delegates
	virtual void OnNavMeshTilesUpdated(const TArray<uint32>& ChangedTiles) override;

	//Broadcasts buffered tile updates every TileBufferInterval seconds via the NavMeshTilesUpdatedDelegate. This function is thread safe.
	UFUNCTION()
	void ProcessQueuedTiles();

	//Delegate Handler
	UFUNCTION()
	void OnNavMeshGeneratedFinishedHandler(ANavigationData* NavData);
};
