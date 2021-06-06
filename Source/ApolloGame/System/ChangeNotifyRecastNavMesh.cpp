// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ChangeNotifyRecastNavMesh.h"
#include "NavigationSystem.h"
#include "Engine/World.h"

//Profiler Integration
DECLARE_LOG_CATEGORY_EXTERN(ApolloNavMesh, Log, All);
DEFINE_LOG_CATEGORY(ApolloNavMesh)

AChangeNotifyRecastNavMesh::AChangeNotifyRecastNavMesh()
{
}

AChangeNotifyRecastNavMesh::AChangeNotifyRecastNavMesh(const FObjectInitializer& ObjectInitializer)
{
}

void AChangeNotifyRecastNavMesh::BeginPlay()
{
	//Call base class BeginPlay
	Super::BeginPlay();

	//Create Timer Handle - for processing the tiles generated
	GetWorld()->GetTimerManager().SetTimer(TileUpdateTimerHandle,this,&AChangeNotifyRecastNavMesh::ProcessQueuedTiles, TileBufferInterval,true);
	//TODO: Double check this as this may create double registrations
	UNavigationSystemV1::GetCurrent(GetWorld())->OnNavigationGenerationFinishedDelegate.RemoveDynamic(this,&AChangeNotifyRecastNavMesh::OnNavMeshGeneratedFinishedHandler);
	UNavigationSystemV1::GetCurrent(GetWorld())->OnNavigationGenerationFinishedDelegate.AddDynamic(this,&AChangeNotifyRecastNavMesh::OnNavMeshGeneratedFinishedHandler);
}

void AChangeNotifyRecastNavMesh::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Clear our timer since the world is being destroyed
	GetWorld()->GetTimerManager().ClearTimer(TileUpdateTimerHandle);

	//Call base class EndPlay
	Super::EndPlay(EndPlayReason);
}

void AChangeNotifyRecastNavMesh::OnNavMeshTilesUpdated(const TArray<uint32>& ChangedTiles)
{
	//Call base class implementation
	Super::OnNavMeshTilesUpdated(ChangedTiles);

	TSet<uint32> updatedTiles;
	//Loop through the tiles and bind the interval and finished delegates
	for (uint32 changedTile : ChangedTiles)
	{
		updatedTiles.Add(changedTile);
		UpdatedTilesIntervalBuffer.Add(changedTile);
		UpdatedTilesUntilFinishedBuffer.Add(changedTile);
	}

	//Call the update immediately delegate
	NavMeshTilesUpdatedImmediateDelegate.Broadcast(updatedTiles);
}

void AChangeNotifyRecastNavMesh::ProcessQueuedTiles()
{
	//Implements a Scope Lock - helps prevents deadlocks due to exceptions
	FScopeLock TileUpdateLock(&TileUpdateLockObject);
	//Print the number of tiles generated
	if(UpdatedTilesIntervalBuffer.Num() > 0)
	{
		UE_LOG(ApolloNavMesh,Log,TEXT("OnNaveMeshTilesUpdated - tile count: %d"), UpdatedTilesIntervalBuffer.Num());
		UpdatedTilesIntervalBuffer.Empty();
	}
}

void AChangeNotifyRecastNavMesh::OnNavMeshGeneratedFinishedHandler(ANavigationData* NavData)
{
	//Implements a Scope Lock - helps prevents deadlocks due to exceptions
	FScopeLock TileUpdateLock(&TileUpdateLockObject);
	//Let the nav data know that we have finished generating tiles
	NavMeshTilesUpdatedUntilFinishedDelegate.Broadcast(UpdatedTilesUntilFinishedBuffer);
	//Move on to the next set of tiles
	UpdatedTilesUntilFinishedBuffer.Empty();
}
