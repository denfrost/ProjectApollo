// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "ApolloGame/System/DTOCoverData.h"

/**
* Asynchronous, non-abandoning task for generating cover points and inserting them into an octree via UApolloCoverSystemLibrary.
*/

class APOLLOGAME_API FNavMeshCoverPointGeneratorTask : public FNonAbandonableTask
{
	//Allows us access to private and protected members
	friend class FAutoDeleteAsyncTask<FNavMeshCoverPointGeneratorTask>;

protected:
	static FVector GetPerpendicularVector(const FVector& Vector);

	//Minimum distance between cover points
	float CoverPointMinDistance = 0.0f;

	//How far to trace from a NavMesh edge towards the inside of the NavMesh "hole"
	const float ScanReach = 100.0f;

	//Distance between an outermost edge of the NavMesh and a cliff, likely because of no NavMesh
	const float CliffEdgeDistance = 70.0f;


	//Offset that gets added to the cliff edge trace. Useful for detecting cliffs on Landscapes
	const float StraightCliffErrorTolerance = 100.0f;

	//Length of the raycast from checking if there's a NavMesh hole along one of the sides of a NavMesh edge
	const float NavMeshHoleCheckReach = 5.0f;

	//Height of the smallest actor that will fit under an overhanging cover. Should be the Crouched Height of the smallest actor in the game.
	const float SmallestAgentHeight;

	//A small Z-axis offset applied to each cover point. This is to prevent small irregularities in the NavMesh from registering as cover.
	const float CoverPointGroundOffset;

	//Distance of the NavMesh from the ground, plus a little extra to make sure we do hit the ground
	//Used for finding cliff edges
	const float NavMeshMaxZDistanceFromGround;

	//Bounding box used to filter out cover points on the edges of the map
	const FBox MapBounds;

	//The bounding box to generate cover points in
	const int32 NavMeshTileIndex;

	//The currently active World
	UWorld* CurrentWorld;

#if DEBUG_RENDERING
	bool bDebugDraw = false;
#endif

	const FVector GetEdgeDir(const FVector& EdgeStartVertex, const FVector& EdgeEndVertex) const;

	//Uses NavMesh raycasts to scan for cover from TraceStart to TraceEnd
	//Builds DTOCoverData for transferring results to the octree
	//True: Cover was found, False: No cover was found
	bool ScanForCoverNavMeshProjection(FDTOCoverData& OutCoverData, const FVector& TraceStart, const FVector& TraceDirection);

	void ProcessEdgeStep(TArray<FDTOCoverData>& OutCoverPointsOfActors, const FVector& EdgeStepVertex, const FVector& EdgeDir);

	//Generates cover points inside the specified bounding box through NavMesh edge-walking
	// Returns the AABB of the NavMesh tile that corresponds to NavMeshTileIndex
	const FBox GenerateCoverInBounds(TArray<FDTOCoverData>& OutCoverPointsOfActors);

	//Find cover points in the bounding box supplied and store them within the cover system
	//But remove any cover points that exist first
	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FNavMeshCoverPointGeneratorTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	public:
	FNavMeshCoverPointGeneratorTask(
		float _CoverPointMinDistance,
		float _SmallestAgentHeight,
		float _CoverPointGroundOffset,
		FBox _MapBounds,
		int32 _NavmeshTileIndex,
		UWorld* _World
	);
};
