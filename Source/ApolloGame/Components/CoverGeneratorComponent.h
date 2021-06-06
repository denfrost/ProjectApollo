// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)
//This is largely based on the Real Time Dynamic Cover System from David Nadaski - https://www.freecodecamp.org/news/real-time-dynamic-cover-system-in-unreal-engine-4-eddb554eaefb/
#pragma once

#include "CoreMinimal.h"

#include "NavigationData.h"
#include "Components/ActorComponent.h"
#include "CoverGeneratorComponent.generated.h"

/*This component is intended for large objects created at runtime that don't move but
 * allow raycasts to pass through (Think Reinhardt's shield from Overwatch)
 *
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class APOLLOGAME_API UCoverGeneratorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCoverGeneratorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Multiply the bounding collision by this and the ScanGrid amount, this is used to adjust the navmesh to ensure it doesn't exceed the bounds of object
	const float BoundingBoxExpansion = 0.5f;

#if DEBUG_RENDERING
	bool bDebugDraw = false;
#endif

	//Cached for easier Destruction handling
	//FBox is an axis-aligned box - used for bounding volumes, collision detection and so on
	FBox OwnerBounds;

	//Has the navmesh already been generated?
	bool bFirstNavMeshGeneration = true;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	//Should cover points be generated when the game starts? Defaults to true, but should be set to false on most occasions. You will need to call the GenerateCoverPoints function directly when this is false
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generation")
	bool bGenerateOnBeginPlay = true;

	//Should cover points be generated on each StaticMesh found within the Owner or around all colliders inside the owner's bounding box. Set to true if the owner would likely intersect with other actors at run time.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generation")
	bool bGeneratePerStaticMesh = false;

	//Density of scan grid (with lower values requiring more traces); Rule of thumb is to shave off a little from the collider radius of the smallest unit capable of reaching cover, typically the smallest radius used by the navmesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scan")
	float ScanGridUnit = 75.0f;

	//Height of the smallest actor that can fit under an overhanging cover. Should be set to the crouched height of the smallest actor from the navmesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Scan")
	float SmallestAgentHeight = 190.0f;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	// UFUNCTION()
	// void OnNavMeshGeneratedFinished(ANavigationData* NavData);

	//Generates cover points around and inside the owner asynchronously via CoverPointGeneratorTask, which saves the results in the game mode's octree
	UFUNCTION(BlueprintCallable, Category = "Generation")
	void GenerateCoverPoints();
};
