// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ApolloCoverSystemLibrary.h"
#include "ApolloGame/Tasks/NavMeshCoverPointGeneratorTask.h"

#if DEBUG_RENDERING
#include "DrawDebugHelpers.h"
#endif

// PROFILER INTEGRATION //
DEFINE_STAT(STAT_GenerateCover);
DEFINE_STAT(STAT_GenerateCoverInBounds);
DEFINE_STAT(STAT_FindCover);

UApolloCoverSystemLibrary* UApolloCoverSystemLibrary::CoverSystemInstance;
bool UApolloCoverSystemLibrary::bShutdown;

UApolloCoverSystemLibrary::UApolloCoverSystemLibrary()
{
	//TODO: take extents of underlying nav mesh instead of using 64,000, check NavData->GetBounds via OnNavMeshUpdated
	CoverOctree = MakeShareable(new TCoverOctree(FVector(0, 0, 0), 64000));
}

UApolloCoverSystemLibrary::~UApolloCoverSystemLibrary()
{
	if (CoverOctree.IsValid())
	{
		//Destroy the Octree upon Destruction
		CoverOctree->Destroy();
		CoverOctree = nullptr;
	}
	ElementToID.Empty();
	CoverObjectToID.Empty();
	CoverSystemInstance = nullptr;
}

void UApolloCoverSystemLibrary::OnBeginPlay()
{
	bShutdown = false;

	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!IsValid(NavSys))
	{
		return;
	}

	//Subscribe to tile update events on navmesh
	const ANavigationData* MainNavData = NavSys->MainNavData;
	if (MainNavData && MainNavData->IsA(AChangeNotifyRecastNavMesh::StaticClass()))
	{
		Navmesh = const_cast<AChangeNotifyRecastNavMesh*>(Cast<AChangeNotifyRecastNavMesh>(MainNavData));
		Navmesh->NavMeshTilesUpdatedBufferedDelegate.
		         AddDynamic(this, &UApolloCoverSystemLibrary::OnNavMeshTilesUpdated);
	}
}

bool ContainsCoverPoint(FCoverPointOctreeElement CoverPoint, TArray<FCoverPointOctreeElement> CoverPointOctreeElements)
{
	for(FCoverPointOctreeElement OctreeElement : CoverPointOctreeElements)
	{
		if(CoverPoint.Data->Location == OctreeElement.Data->Location)
		{
			return true;
		}
	}
	return false;
}

bool UApolloCoverSystemLibrary::GetElementID(FOctreeElementId2& OutElementID, const FVector ElementLocation) const
{
	if (bShutdown)
	{
		return false;
	}

	const FOctreeElementId2* Element = ElementToID.Find(ElementLocation);
	if (!Element || !Element->IsValidId())
	{
		return false;
	}
	OutElementID = *Element;
	return true;
}

bool UApolloCoverSystemLibrary::RemoveIDToElementMapping(const FVector ElementLocation)
{
	if (bShutdown)
	{
		return false;
	}

	return ElementToID.Remove(ElementLocation) > 0;
}

FBox UApolloCoverSystemLibrary::EnlargeAABB(FBox Box)
{
	return Box.ExpandBy(FVector(
		(Box.Max.X - Box.Min.X) * 0.5f,
		(Box.Max.Y - Box.Min.Y) * 0.5f,
		(Box.Max.Z - Box.Min.Z) * 0.5f
	));
}

UApolloCoverSystemLibrary* UApolloCoverSystemLibrary::GetInstance(UWorld* World)
{
	if (IsShuttingDown())
	{
		return nullptr;
	}

	if (!IsValid(CoverSystemInstance))
	{
		//Initialize Singleton

		CoverSystemInstance = NewObject<UApolloCoverSystemLibrary>(World, "ApolloCoverSystem");
		check(CoverSystemInstance);
		CoverSystemInstance->OnBeginPlay();

		//reset persistent profiler stats
		SET_DWORD_STAT(STAT_GenerateCoverHistoricalCount, 0);
		SET_FLOAT_STAT(STAT_GenerateCoverAverageTime, 0.0f);
		SET_DWORD_STAT(STAT_FindCoverHistoricalCount, 0);
		SET_FLOAT_STAT(STAT_FindCoverTotalTimeSpent, 0.0f);
		SET_DWORD_STAT(STAT_TaskCount, 0);
		
	}
	return CoverSystemInstance;
}

bool UApolloCoverSystemLibrary::IsShuttingDown()
{
	return bShutdown;
}

UApolloCoverSystemLibrary* UApolloCoverSystemLibrary::GetCoverSystem(UObject* WorldContextObject)
{
	UWorld* World = nullptr;
	if (WorldContextObject)
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	return World ? GetInstance(World) : nullptr;
}

void UApolloCoverSystemLibrary::OnNavMeshTilesUpdated(const TSet<uint32>& UpdatedTiles)
{
	if (IsShuttingDown())
	{
		return;
	}

	//Regenerate cover points within the new tiles
	TArray<const AActor*> DirtyCoverActors;
	for (uint32 TileIDx : UpdatedTiles)
	{
		//Get the bounding box of the updated tile
		//FBox TileBounds = Navmesh->GetNavMeshTileBounds(TileIDx);

#if DEBUG_RENDERING
		// DrawDebugXXX calls may crash UE4 when not called from the main thread, so start synchronous tasks in case we're planning on drawing debug shapes
		if (bDebugDraw)
			(new FAutoDeleteAsyncTask<FNavMeshCoverPointGeneratorTask>(
				CoverPointMinDistance,
				SmallestAgentHeight,
				CoverPointGroundOffset,
				MapBounds,
				TileIDx,
				GetWorld()
			))->StartSynchronousTask();
		else
#endif
			(new FAutoDeleteAsyncTask<FNavMeshCoverPointGeneratorTask>(
				CoverPointMinDistance,
				SmallestAgentHeight,
				CoverPointGroundOffset,
				MapBounds,
				TileIDx,
				GetWorld()
			))->StartBackgroundTask();
	}
}


void UApolloCoverSystemLibrary::FindCoverPoints_Box(TArray<FCoverPointOctreeElement>& OutCoverPoints,
                                                    const FBox& QueryBox) const
{
	if (IsShuttingDown())
	{
		return;
	}

	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_ReadOnly);
	CoverOctree->FindCoverPoints_Box(OutCoverPoints, QueryBox);
}

void UApolloCoverSystemLibrary::FindCoverPoints_Sphere(TArray<FCoverPointOctreeElement>& OutCoverPoints,
                                                       const FSphere& QuerySphere) const
{
	if (IsShuttingDown())
	{
		return;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_ReadOnly);
	CoverOctree->FindCoverPoints_Sphere(OutCoverPoints, QuerySphere);
}

void UApolloCoverSystemLibrary::OptimizeOctree() const
{
	//Optimize octree by reducing it to the smallest possible size
	CoverOctree->ShrinkElements();
}

void UApolloCoverSystemLibrary::AddCoverPoints(const TArray<FDTOCoverData>& CoverPointDTOs)
{
	if (IsShuttingDown())
	{
		return;
	}

	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	for (FDTOCoverData CoverData : CoverPointDTOs)
	{
		CoverOctree->AddCoverPoint(CoverData, CoverPointMinDistance * 0.9f);
	}

	OptimizeOctree();
}

void UApolloCoverSystemLibrary::RemoveStaleCoverPoints(FBox Area)
{
	if (IsShuttingDown())
	{
		return;
	}

	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);

	//Increase the clean-up area to 1.5x its size
	Area = EnlargeAABB(Area);

	//Find all cover points within the area
	TArray<FCoverPointOctreeElement> CoverPoints;
	CoverOctree->FindCoverPoints_Box(CoverPoints, Area);

	//Check if the cover point still has an owner
	//And if it falls in the same location as when it was generated
	for (FCoverPointOctreeElement CoverPoint : CoverPoints)
	{
		FNavLocation NavLocation;
		if (IsValid(CoverPoint.GetOwner()) && UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(
			CoverPoint.Data->Location, NavLocation, FVector(0.1f, 0.1f, CoverPointGroundOffset)))
		{
			FOctreeElementId2 ElementId2;
			GetElementID(ElementId2, CoverPoint.Data->Location);
			//Remove the cover point from octree
			if (ElementId2.IsValidId())
			{
				CoverOctree->RemoveElement(ElementId2);
			}

			//Remove cover point from element to id and object to location maps
			RemoveIDToElementMapping(CoverPoint.Data->Location);
			CoverObjectToID.RemoveSingle(CoverPoint.Data->CoverObject, CoverPoint.Data->Location);
		}
	}
	OptimizeOctree();
}

void UApolloCoverSystemLibrary::RemoveStaleCoverPoints(FVector Origin, FVector Extent)
{
	if (IsShuttingDown())
	{
		return;
	}
	RemoveStaleCoverPoints(FBoxCenterAndExtent(Origin, Extent * 2.0f).GetBox());
}

void UApolloCoverSystemLibrary::RemoveCoverPointsOfObject(const AActor* CoverObject)
{
	if (IsShuttingDown())
	{
		return;
	}
	
	if (CoverSystemInstance && !IsShuttingDown())
	{
		FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);

		TArray<FVector> CoverPointLocations;

		CoverObjectToID.MultiFind(CoverObject, CoverPointLocations, false);

		for (const FVector CoverPointLocation : CoverPointLocations)
		{
			FOctreeElementId2 ElementId2;
			GetElementID(ElementId2, CoverPointLocation);
			CoverOctree->RemoveElement(ElementId2);
			RemoveIDToElementMapping(CoverPointLocation);
			CoverObjectToID.Remove(CoverObject);

#if DEBUG_RENDERING
			if (bDebugDraw)
			{
				DrawDebugSphere(GetWorld(), CoverPointLocation, 20.0f, 4, FColor::Red, true, -1.0f, 0, 2.0f);
			}
#endif
		}
		OptimizeOctree();
	}
}

void UApolloCoverSystemLibrary::RemoveAll()
{
	if (bShutdown)
	{
		return;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	//Destroy the octree
	if (CoverOctree.IsValid())
	{
		CoverOctree->Destroy();
		CoverOctree = nullptr;
	}

	//Remove id to element mappings
	ElementToID.Empty();

	//Create a new octree
	CoverOctree = MakeShareable(new TCoverOctree(FVector(0, 0, 0), 64000));
}

void UApolloCoverSystemLibrary::AssignIDToElement(const FVector ElementLocation, FOctreeElementId2 ID)
{
	if (IsShuttingDown())
	{
		return;
	}
	ElementToID.Add(ElementLocation, ID);
}

bool UApolloCoverSystemLibrary::HoldCover(FVector ElementLocation)
{
	if (bShutdown)
	{
		return false;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	FOctreeElementId2 ElemID;
	if (!GetElementID(ElemID, ElementLocation))
	{
		return false;
	}
	return CoverOctree->HoldCover(ElemID);
}

bool UApolloCoverSystemLibrary::ReleaseCover(FVector ElementLocation)
{
	if (bShutdown)
	{
		return false;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	FOctreeElementId2 ElemID;
	if (!GetElementID(ElemID, ElementLocation))
	{
		return false;
	}
	return CoverOctree->ReleaseCover(ElemID);
}
