// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "CoverGeneratorComponent.h"

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

	// ...
	
}


// Called every frame
void UCoverGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCoverGeneratorComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
}

// void UCoverGeneratorComponent::OnNavMeshGeneratedFinished(ANavigationData* NavData)
// {
// 	GenerateCoverPoints();
// }

void UCoverGeneratorComponent::GenerateCoverPoints()
{
}

