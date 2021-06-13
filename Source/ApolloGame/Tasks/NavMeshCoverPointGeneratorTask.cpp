// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "NavMeshCoverPointGeneratorTask.h"
#include "LandscapeProxy.h"
#include "ApolloGame/System/ApolloCoverSystemLibrary.h"
#include "NavMesh/RecastNavMesh.h"
#include "Detour/DetourNavMesh.h"

#if DEBUG_RENDERING
#include "DrawDebugHelpers.h"
#endif

FVector FNavMeshCoverPointGeneratorTask::GetPerpendicularVector(const FVector& Vector)
{
	return FVector(Vector.Y, -Vector.X, Vector.Z);
}

const FVector FNavMeshCoverPointGeneratorTask::GetEdgeDir(const FVector& EdgeStartVertex,
                                                          const FVector& EdgeEndVertex) const
{
	return (EdgeEndVertex - EdgeStartVertex).GetUnsafeNormal();
}

bool FNavMeshCoverPointGeneratorTask::ScanForCoverNavMeshProjection(FDTOCoverData& OutCoverData,
                                                                    const FVector& TraceStart,
                                                                    const FVector& TraceDirection)
{
	const FVector TraceEndNavMesh = TraceStart + (TraceDirection * NavMeshHoleCheckReach);
	// need to keep the navmesh raycast as short as possible
	const FVector TraceEndPhysX = TraceStart + (TraceDirection * ScanReach);
	// the physx raycast is longer so that it may reach slanted geometry, e.g. ramps
	const FVector SmallestAgentHeightOffset = FVector(0.0f, 0.0f, SmallestAgentHeight);


	//Project the point onto the navmesh: If successful, then it is not a NavMesh hole, so we return false
	FNavLocation NavLocation;
	if (UNavigationSystemV1::GetCurrent(CurrentWorld)->ProjectPointToNavigation(
		TraceEndNavMesh, NavLocation, FVector(0.1f, 0.1f, 0.1f)))
	{
		return false;
	}

	//To get the cover object within the hole, We still need to do a raycast in its general direction, at the SmallestAgentHeight to ensure that the cover is tall enough
	FHitResult OutHit;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.TraceTag = "CoverGen_ScanForCoverNavMeshProjection";

	bool bIsSuccessful = CurrentWorld->LineTraceSingleByChannel(OutHit, TraceStart + SmallestAgentHeightOffset,
	                                                            TraceEndPhysX + SmallestAgentHeightOffset,
	                                                            ECollisionChannel::ECC_GameTraceChannel5,
	                                                            CollisionQueryParams);

	//TODO: Comment out if not needed - this is ledge detection logic
	if (!bIsSuccessful)
	{
		// if we didn't hit an object with the XY-parallel ray then cast another one towards the ground from an extended location, down along the Z-axis
		// this ensures that we pick up the edges of cliffs, which are valid cover points against units below, while also discarding flat planes that tend to creep up along navmesh tile boundaries
		// if this ray doesn't hit anything then we've found a cliff's edge
		// if it hits, then cast another, similar, but slightly slanted ray to account for any non-perfectly straight cliff walls e.g. that of landscapes
		FHitResult hitCliff;
		const FVector cliffTraceStart = TraceEndNavMesh + (TraceDirection * CliffEdgeDistance);
		bIsSuccessful = !CurrentWorld->LineTraceSingleByChannel(hitCliff, cliffTraceStart, cliffTraceStart - SmallestAgentHeightOffset, ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);

		if (!bIsSuccessful)
			// this is the slightly slanted, 2nd ray
			bIsSuccessful = !CurrentWorld->LineTraceSingleByChannel(hitCliff, cliffTraceStart, cliffTraceStart - SmallestAgentHeightOffset + (TraceDirection * StraightCliffErrorTolerance), ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);

		if (bIsSuccessful)
			// now that we've established that it's a cliff's edge, we need to trace into the ground to find the "cliff object"
			bIsSuccessful = CurrentWorld->LineTraceSingleByChannel(OutHit, TraceStart, TraceStart - FVector(0.0f, 0.0f, NavMeshMaxZDistanceFromGround), ECollisionChannel::ECC_GameTraceChannel1, CollisionQueryParams);

	}


	if (!bIsSuccessful)
	{
		return false;
	}

	//Force fields are handled by FActorCoverPointGeneratorTask instead
	if (ECC_GameTraceChannel2 == OutHit.Actor->GetRootComponent()->GetCollisionObjectType())
	{
		return false;
	}

	OutCoverData = FDTOCoverData(OutHit.GetActor(), TraceStart, false);
	return true;
}

void FNavMeshCoverPointGeneratorTask::ProcessEdgeStep(TArray<FDTOCoverData>& OutCoverPointsOfActors,
                                                      const FVector& EdgeStepVertex, const FVector& EdgeDir)
{
	//Checks if the given location is within the map bounds
	if (!MapBounds.IsInside(EdgeStepVertex))
	{
		return;
	}

	FDTOCoverData CoverData;
	//Check if we have reached the map edge
	for (int DirectionMultiplier = 1; DirectionMultiplier > -2; DirectionMultiplier -= 2)
	{
		if (ScanForCoverNavMeshProjection(CoverData, EdgeStepVertex,
		                                  GetPerpendicularVector(EdgeDir) * DirectionMultiplier))
		{
			OutCoverPointsOfActors.Add(CoverData);
			return;
		}
	}
}

const FBox FNavMeshCoverPointGeneratorTask::GenerateCoverInBounds(TArray<FDTOCoverData>& OutCoverPointsOfActors)
{
	//Profiler Info
	SCOPE_CYCLE_COUNTER(STAT_GenerateCoverInBounds);
	INC_DWORD_STAT(STAT_GenerateCoverHistoricalCount);
	SCOPE_SECONDS_ACCUMULATOR(STAT_GenerateCoverAverageTime);

	const ARecastNavMesh* NavData = Cast<ARecastNavMesh>(UNavigationSystemV1::GetCurrent(CurrentWorld)->MainNavData);
	FRecastDebugGeometry NavGeo;
	NavGeo.bGatherNavMeshEdges = true;

	//Get the Nav vertices from recast via a batch query
	NavData->BeginBatchQuery();
	NavData->GetDebugGeometry(NavGeo, NavMeshTileIndex);
	NavData->FinishBatchQuery();

	//Process navmesh Vertices (Called Nav Mesh Edges in editor)
	TArray<FVector>& Vertices = NavGeo.NavMeshEdges;
	const int NumOfVertices = Vertices.Num();
	if (NumOfVertices > 1)
	{
		// const FVector FirstEdgeDir = GetEdgeDir(Vertices[0], Vertices[1]);
		// const FVector LastEdgeDir = GetEdgeDir(Vertices[NumOfVertices - 2], Vertices[NumOfVertices - 1]);
		for (int i = 0; i < NumOfVertices; i += 2)
		{
			const FVector EdgeStartVertex = Vertices[i];
			const FVector EdgeEndVertex = Vertices[i + 1];
			const FVector Edge = EdgeEndVertex - EdgeStartVertex;
			const FVector EdgeDir = Edge.GetUnsafeNormal();
#if DEBUG_RENDERING
			if (bDebugDraw)
			{
				DrawDebugDirectionalArrow(CurrentWorld, EdgeStartVertex, EdgeEndVertex, 200.0f, FColor::Purple, true,
				                          -1.0f, 0, 2.0f);
			}
#endif
			//Process edges in CoverPointMinDistance increments
			const int EdgeSteps = Edge.Size() / CoverPointMinDistance;
			for (int iEdgeStep = 0; iEdgeStep < EdgeSteps; iEdgeStep++)
			{
				//Check to the left, optionally to the right, of the vertex's location for blocking geometry
				//If geometry blocks the raycast then the vertex is marked as a cover point
				ProcessEdgeStep(OutCoverPointsOfActors,
				                EdgeStartVertex + (iEdgeStep * CoverPointMinDistance * EdgeDir) + FVector(
					                0.0f, 0.0f, CoverPointGroundOffset), EdgeDir);

				//Process the first step if the edge was shorter than the Min Distance
				if (EdgeSteps == 0)
				{
					ProcessEdgeStep(OutCoverPointsOfActors,
					                EdgeStartVertex + FVector(0.0f, 0.0f, CoverPointGroundOffset), EdgeDir);
				}
				//Process the end vertex. Most of the time it's left out of the for loop, but we will process the same vertex twice (likely to not happen because of floating point division)
				ProcessEdgeStep(OutCoverPointsOfActors, EdgeStartVertex + FVector(0.0f, 0.0f, CoverPointGroundOffset),
				                EdgeDir);

				//Process the end vertex again, but with the edge direction rotated by 45 degrees
				//Process the end vertex. Most of the time it's left out of the for loop, but we will process the same vertex twice (likely to not happen because of floating point division)
				ProcessEdgeStep(OutCoverPointsOfActors, EdgeStartVertex + FVector(0.0f, 0.0f, CoverPointGroundOffset),
				                FVector(FVector2D(EdgeDir).GetRotated(45.0f), EdgeDir.Z));
			}
		}
	}

	//Return the Bounding box of the NavMesh tile that's been processed, expanded by minimum tile height on the Z
	const ARecastNavMesh* RecastNavMesh = Cast<ARecastNavMesh>(
		UNavigationSystemV1::GetCurrent(CurrentWorld)->MainNavData);
	FBox NavMeshBounds = NavData->GetNavMeshTileBounds(NavMeshTileIndex);
	float NavMeshTileHeight = RecastNavMesh->GetRecastMesh()->getParams()->tileHeight;
	if (NavMeshTileHeight > 0)
	{
		NavMeshBounds = NavMeshBounds.ExpandBy(FVector(0.0f, 0.0f, NavMeshTileHeight * 0.5f));
	}
	return NavMeshBounds;
}

void FNavMeshCoverPointGeneratorTask::DoWork()
{
	//Profiler data
	SCOPE_CYCLE_COUNTER(STAT_GenerateCover);
	INC_DWORD_STAT(STAT_GenerateCoverHistoricalCount);
	SCOPE_SECONDS_ACCUMULATOR(STAT_GenerateCoverAverageTime);
	INC_DWORD_STAT(STAT_TaskCount);

	bool bIsShuttingDown = UApolloCoverSystemLibrary::IsShuttingDown();

#if DEBUG_RENDERING
	if (UApolloCoverSystemLibrary::IsShuttingDown())
	{
		return;
	}
	bDebugDraw = UApolloCoverSystemLibrary::GetInstance(CurrentWorld)->bDebugDraw;
#endif

	//Generate Cover Points
	TArray<FDTOCoverData> CoverPoints;
	FBox NavMeshTileArea = GenerateCoverInBounds(CoverPoints);

	//Remove any cover points that don't fall on the NavMesh anymore
	//Happens when a newly added cover object is placed on top of previously generated cover points
	if (UApolloCoverSystemLibrary::IsShuttingDown())
	{
		return;
	}
	//TODO: May want to delete this - a few more cover points might be left over upon removal at the expense of fewer cover points. Most apparent near ledges. Not a big deal in the end
	UApolloCoverSystemLibrary::GetInstance(CurrentWorld)->RemoveStaleCoverPoints(NavMeshTileArea);

	//Add the generated cover points to octree in a single batch
	if (UApolloCoverSystemLibrary::bShutdown)
	{
		return;
	}
	UApolloCoverSystemLibrary::GetInstance(CurrentWorld)->AddCoverPoints(CoverPoints);

#if DEBUG_RENDERING
	for (FDTOCoverData CoverPoint : CoverPoints)
	{
		if (bDebugDraw)
		{
			DrawDebugSphere(CurrentWorld, CoverPoint.Location, 20.0f, 4, FColor::Blue, true);
#endif
			DEC_DWORD_STAT(STAT_TaskCount);
		}
	}
}

FNavMeshCoverPointGeneratorTask::FNavMeshCoverPointGeneratorTask(float _CoverPointMinDistance,
                                                                 float _SmallestAgentHeight,
                                                                 float _CoverPointGroundOffset, FBox _MapBounds,
                                                                 int32 _NavmeshTileIndex, UWorld* _World)
	: CoverPointMinDistance(_CoverPointMinDistance),
	  SmallestAgentHeight(_SmallestAgentHeight),
	  CoverPointGroundOffset(_CoverPointGroundOffset),
	  NavMeshMaxZDistanceFromGround(_CoverPointGroundOffset * 3.0f),
	  MapBounds(_MapBounds),
	  NavMeshTileIndex(_NavmeshTileIndex),
	  CurrentWorld(_World)
{
}
