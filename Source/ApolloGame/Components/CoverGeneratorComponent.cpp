// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "CoverGeneratorComponent.h"

#include "NavigationSystem.h"
#include "ApolloGame/AI/Tasks/ActorCoverPointGeneratorTask.h"
#include "ApolloGame/System/ApolloCoverSystemLibrary.h"

// Sets default values for this component's properties
UCoverGeneratorComponent::UCoverGeneratorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCoverGeneratorComponent::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin;
	FVector Extent;
	GetOwner()->GetActorBounds(false,Origin,Extent);
	OwnerBounds = FBoxCenterAndExtent(Origin,Extent).GetBox();

	//Generate cover points NEAR begin play, if requested
	//have to wait for the navmesh to finish generation first
	if(bGenerateOnBeginPlay)
	{
		UNavigationSystemV1::GetCurrent(GetWorld())->OnNavigationGenerationFinishedDelegate.AddDynamic(this,&UCoverGeneratorComponent::OnNavMeshGeneratedFinished);
	}
	
}


// Called every frame
void UCoverGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoverGeneratorComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	//Remove owner's cover points from the map upon destruction
	if(UApolloCoverSystemLibrary::IsShuttingDown())
	{
		return;
	}
	UApolloCoverSystemLibrary::GetInstance(GetWorld())->RemoveCoverPointsOfObject(GetOwner());
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}


void UCoverGeneratorComponent::OnNavMeshGeneratedFinished(ANavigationData* NavData)
{
	GenerateCoverPoints();
}

void UCoverGeneratorComponent::GenerateCoverPoints()
{
#if DEBUG_RENDERING
	if(UApolloCoverSystemLibrary::IsShuttingDown())
	{
		return;
	}
	bDebugDraw = UApolloCoverSystemLibrary::GetInstance(GetWorld())->bDebugDraw;
#endif

	//Spawn the cover generator task
#if DEBUG_RENDERING
	if (bDebugDraw)
	{
		(new FAutoDeleteAsyncTask<FActorCoverPointGeneratorTask>(
			GetOwner(),
			GetWorld(),
			BoundingBoxExpansion,
			ScanGridUnit,
			SmallestAgentHeight,
			bGeneratePerStaticMesh
			))->StartSynchronousTask();
	}
	else
#endif
	(new FAutoDeleteAsyncTask<FActorCoverPointGeneratorTask>(
		GetOwner(),
		GetWorld(),
		BoundingBoxExpansion,
		ScanGridUnit,
		SmallestAgentHeight,
		bGeneratePerStaticMesh
	))->StartBackgroundTask();
	
}

