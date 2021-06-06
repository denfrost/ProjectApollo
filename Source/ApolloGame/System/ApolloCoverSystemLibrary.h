// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"

#include "ChangeNotifyRecastNavMesh.h"
#include "ApolloGame/NavMesh/CoverOctree.h"
#include "NavigationSystem.h"
#include "NavigationOctree.h"
#include "NavMesh/RecastNavMesh.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/ScopeRWLock.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DTOCoverData.h"
#include "ApolloCoverSystemLibrary.generated.h"

// PROFILER INTEGRATION //

DECLARE_STATS_GROUP(TEXT("CoverSystem"), STATGROUP_CoverSystem, STATCAT_Cover);

DECLARE_CYCLE_STAT_EXTERN(TEXT("Generate Cover / Full"), STAT_GenerateCover, STATGROUP_CoverSystem, APOLLOGAME_API);
DECLARE_CYCLE_STAT_EXTERN(TEXT("Generate Cover / GenerateCoverInBounds"), STAT_GenerateCoverInBounds,
                          STATGROUP_CoverSystem, APOLLOGAME_API);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("Generate Cover - Historical Count"), STAT_GenerateCoverHistoricalCount,
                               STATGROUP_CoverSystem);
DECLARE_FLOAT_ACCUMULATOR_STAT(TEXT("Generate Cover - Total Time Spent"), STAT_GenerateCoverAverageTime,
                               STATGROUP_CoverSystem);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("Generate Cover - Active Tasks"), STAT_TaskCount, STATGROUP_CoverSystem);

DECLARE_CYCLE_STAT_EXTERN(TEXT("Find Cover"), STAT_FindCover, STATGROUP_CoverSystem, APOLLOGAME_API);
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("Find Cover - Historical Count"), STAT_FindCoverHistoricalCount,
                               STATGROUP_CoverSystem);
DECLARE_FLOAT_ACCUMULATOR_STAT(TEXT("Find Cover - Total Time Spent"), STAT_FindCoverTotalTimeSpent,
                               STATGROUP_CoverSystem);

/**
* Singleton. The cover system contains the cover points octree and is also responsible for hooking into navmesh events to trigger the real-time dynamic (re)generation of cover.
*/
UCLASS()
class APOLLOGAME_API UApolloCoverSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static UApolloCoverSystemLibrary* CoverSystemInstance;

	//Constructor
	UApolloCoverSystemLibrary();

	virtual ~UApolloCoverSystemLibrary() override;
private:
	// Density of the scan grid (lower number -> more traces).
	// Guideline: should be a bit less than the capsule radius of the smallest unit capable of getting into cover, which is normally == smallest radius used for navigation by the navmesh.
	// Used by FTileBasedCoverPointGeneratorTask
	const float ScanGridUnit = 38.0f;

	// Minimum distance between cover points.
	// For the demo, this is UCoverFinderService::WeaponLeanOffset * 2
	// Used by FNavmeshCoverPointGeneratorTask.
	const float CoverPointMinDistance = 2 * 30.0f;

	// Height of the smallest actor that will ever fit under an overhanging cover. Should normally be the CROUCHED height of the smallest actor in the game. Not counting bunnies. Bunnies are useless.
	const float SmallestAgentHeight = 140.0f;

	// A small Z-axis offset applied to each cover point. This is to prevent small irregularities in the navmesh from registering as cover.
	const float CoverPointGroundOffset = 10.0f;

	// Thread lock for CoverOctree and ElementToIDLockObject
	mutable FRWLock CoverDataLockObject;

	// The cover point octree
	// NOT THREAD-SAFE! Use the corresponding thread-safe functions instead.
	TSharedPtr<TCoverOctree, ESPMode::ThreadSafe> CoverOctree;

	// Maps cover point locations to their ids
	// NOT THREAD-SAFE! Use the corresponding thread-safe functions instead.
#if ENGINE_MINOR_VERSION < 26
	TMap<const FVector, FOctreeElementId> ElementToID;
#else
	TMap<const FVector, FOctreeElementId2> ElementToID;
#endif

	// Maps cover objects to their cover point locations
	TMultiMap<TWeakObjectPtr<const AActor>, FVector> CoverObjectToID;

	// // Our custom navmesh
	AChangeNotifyRecastNavMesh* Navmesh;

	// Must be explicitly called by the object that is instantiating the UApolloCoverSystemLibrary.
	UFUNCTION()
	void OnBeginPlay();

	// Finds the element id of the supplied vector. Thread-safe.
	// Returns false if the id wasn't found or is no longer valid.
#if ENGINE_MINOR_VERSION < 26
	bool GetElementID(FOctreeElementId& OutElementID, const FVector ElementLocation) const;
#else
	bool GetElementID(FOctreeElementId2& OutElementID, const FVector ElementLocation) const;
#endif

	// Thread-safe Remove() from ElementToID.
	// Returns true if any elements were removed, false if none.
	bool RemoveIDToElementMapping(const FVector ElementLocation);

	// Enlarges the supplied box to x1.5 its size
	FBox EnlargeAABB(FBox Box);

public:
	// Processing should stop when this is true.
	static bool bShutdown;

	// Enables debug drawing.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDebugDraw = false;

	// AABB used to filter out cover points on the edges of the map.
	FBox MapBounds;

	// Singleton accessor.
	static UApolloCoverSystemLibrary* GetInstance(UWorld* World);

	//Check if the game is ending
	bool static IsShuttingDown();

	// Singleton accessor for Blueprints.
	UFUNCTION(BlueprintPure, Category = "Cover", meta = (WorldContext = "WorldContextObject"))
	static UApolloCoverSystemLibrary* GetCoverSystem(UObject* WorldContextObject);

	// Callback for navmesh tile updates.
	UFUNCTION()
	void OnNavMeshTilesUpdated(const TSet<uint32>& UpdatedTiles);

	// Thread-safe wrapper for TCoverOctree::FindCoverPoints()
	// Finds cover points that intersect the supplied box. 
	void FindCoverPoints(TArray<FCoverPointOctreeElement>& OutCoverPoints, const FBox& QueryBox) const;
	
	// Thread-safe wrapper for TCoverOctree::FindCoverPoints()
	// Finds cover points that intersect the supplied sphere.
	void FindCoverPoints(TArray<FCoverPointOctreeElement>& OutCoverPoints, const FSphere& QuerySphere) const;
	
	// Adds a set of cover points to the octree in a single, thread-safe batch.
	void AddCoverPoints(const TArray<FDTOCoverData>& CoverPointDTOs);

	// Removes cover points within the specified area that don't fall on the navmesh or don't have an owner anymore.
	// Useful for trimming areas around deleted objects and dynamically placed ones.
	void RemoveStaleCoverPoints(FBox Area);

	// Blueprint-friendly version of the above.
	// Multiples Extent by 2.
	UFUNCTION(BlueprintCallable)
	void RemoveStaleCoverPoints(FVector Origin, FVector Extent);

	UFUNCTION(BlueprintCallable)
	void RemoveCoverPointsOfObject(const AActor* CoverObject);

	// Resets the octree, erasing all its data.
	UFUNCTION(BlueprintCallable)
	void RemoveAll();

	// Wrapper for Add() on ElementToID.
	// Not thread-safe and shouldn't be called explicitly. Public because of FCoverPointOctreeSemantics::SetElementId().
	// Automatically wrapped in a thread-safe context as it is a side-effect of AddCoverPoint(), which is always thread-safe.
#if ENGINE_MINOR_VERSION < 26
	void AssignIDToElement(const FVector ElementLocation, FOctreeElementId ID);
#else
	void AssignIDToElement(const FVector ElementLocation, FOctreeElementId2 ID);
#endif

	// Mark the cover at the supplied location as taken.
	// Returns true if the cover wasn't already taken, false if it was or an error has occurred, e.g. the cover no longer exists.
	UFUNCTION(BlueprintCallable)
	bool HoldCover(FVector ElementLocation);

	// Releases a cover that was taken.
	// Returns true if the cover was taken before, false if it wasn't or an error has occurred, e.g. the cover no longer exists.
	UFUNCTION(BlueprintCallable)
	bool ReleaseCover(FVector ElementLocation);
};
