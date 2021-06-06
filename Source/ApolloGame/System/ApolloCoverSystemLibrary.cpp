// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ApolloCoverSystemLibrary.h"

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
	CoverOctree = MakeShareable(new TCoverOctree(FVector(0,0,0),64000));
}

UApolloCoverSystemLibrary::~UApolloCoverSystemLibrary()
{
	if(CoverOctree.IsValid())
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
	if(!IsValid(NavSys))
	{
		return;
	}

	//Subscribe to tile update events on navmesh
	const ANavigationData* mainNavData = NavSys->MainNavData;
	if(mainNavData && mainNavData->IsA(AChangeNotifyRecastNavMesh::StaticClass()))
	{
		Navmesh = const_cast<AChangeNotifyRecastNavMesh*>(Cast<AChangeNotifyRecastNavMesh>(mainNavData));
		Navmesh->NavMeshTilesUpdatedBufferedDelegate.AddDynamic(this, &UApolloCoverSystemLibrary::OnNavMeshTilesUpdated);
	}
}

bool UApolloCoverSystemLibrary::GetElementID(FOctreeElementId2& OutElementID, const FVector ElementLocation) const
{
	if(bShutdown)
	{
		return false;
	}

	const FOctreeElementId2* Element = ElementToID.Find(ElementLocation);
	if(!Element || !Element->IsValidId())
	{
		return false;
	}
	OutElementID = *Element;
	return true;
}

bool UApolloCoverSystemLibrary::RemoveIDToElementMapping(const FVector ElementLocation)
{
	if(bShutdown)
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
	if(IsShuttingDown())
	{
		return nullptr;
	}

	if(!IsValid(CoverSystemInstance))
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
}

void UApolloCoverSystemLibrary::FindCoverPoints(TArray<FCoverPointOctreeElement>& OutCoverPoints,
	const FBox& QueryBox) const
{
}

void UApolloCoverSystemLibrary::FindCoverPoints(TArray<FCoverPointOctreeElement>& OutCoverPoints,
	const FSphere& QuerySphere) const
{
}

void UApolloCoverSystemLibrary::AddCoverPoints(const TArray<FDTOCoverData>& CoverPointDTOs)
{
}

void UApolloCoverSystemLibrary::RemoveStaleCoverPoints(FBox Area)
{
}

void UApolloCoverSystemLibrary::RemoveStaleCoverPoints(FVector Origin, FVector Extent)
{
}

void UApolloCoverSystemLibrary::RemoveCoverPointsOfObject(const AActor* CoverObject)
{
}

void UApolloCoverSystemLibrary::RemoveAll()
{
	if(bShutdown)
	{
		return;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	//Destroy the octree
	if(CoverOctree.IsValid())
	{
		CoverOctree->Destroy();
		CoverOctree = nullptr;
	}

	//Remove id to element mappings
	ElementToID.Empty();

	//Create a new octree
	CoverOctree = MakeShareable(new TCoverOctree(FVector(0,0,0),64000));
}

void UApolloCoverSystemLibrary::AssignIDToElement(const FVector ElementLocation, FOctreeElementId2 ID)
{
}

bool UApolloCoverSystemLibrary::HoldCover(FVector ElementLocation)
{
	if(bShutdown)
	{
		return false;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	FOctreeElementId2 ElemID;
	if(!GetElementID(ElemID, ElementLocation))
	{
		return false;
	}
	return CoverOctree->HoldCover(ElemID);
}

bool UApolloCoverSystemLibrary::ReleaseCover(FVector ElementLocation)
{
	if(bShutdown)
	{
		return false;
	}
	FRWScopeLock CoverDataLock(CoverDataLockObject, FRWScopeLockType::SLT_Write);
	FOctreeElementId2 ElemID;
	if(!GetElementID(ElemID, ElementLocation))
	{
		return false;
	}
	return CoverOctree->ReleaseCover(ElemID);
	
}
