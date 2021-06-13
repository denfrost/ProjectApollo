// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AIController.h"
#include "Engine/World.h"
#include "ApolloGame/Debug/CoverFinderVisData.h"
#include "ApolloGame/NavMesh/CoverPointOctreeElement.h"

#include "CoverFinderService.generated.h"

/**
 * 
 */
UCLASS()
class APOLLOGAME_API UCoverFinderService : public UBTService
{
	GENERATED_BODY()

private:
	// Should be the same as the one defined in the Cover System.
	const float CoverPointGroundOffset = 10.0f;

	const FName Key_VisData = FName("VisData");

	static FVector GetPerpendicularVector(const FVector& Vector);
	// Gather, filter and sort cover points.
	void GetCoverPoints(
		TArray<FCoverPointOctreeElement>& OutCoverPoints,
		UWorld* World,
		const FVector& PawnLocation,
		const FVector& EnemyLocation,
		UCoverFinderVisData& DebugData,
		const bool bUnitDebug = false) const;

	// Checks if there's clear line of sight to the enemy when leaning to the right.
	bool CheckHitByLeaning(
		const FVector& CoverLocation,
		const ACharacter* OurUnit,
		const AActor* TargetEnemy,
		UWorld* World,
		UCoverFinderVisData& DebugData,
		const bool bUnitDebug = false) const;

	bool EvaluateCoverPoint(
		const FCoverPointOctreeElement CoverPoint,
		const ACharacter* Character,
		const float CharEyeHeight,
		const AActor* TargetEnemy,
		const FVector& EnemyLocation,
		UWorld* World,
		UCoverFinderVisData& DebugData,
		const bool bUnitDebug = false) const;

	public:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector DrawDebug;

	// Stores the calculated result here [vector]
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector OutputVector;

	// Our target [actor]
	UPROPERTY(EditAnywhere, Category = Blackboard)
	FBlackboardKeySelector Enemy;

	// Our max attack range
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float AttackRange = 1000.0f;

	// Our min attack range
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float MinAttackRange = 100.0f;

	// How much our weapon moves horizontally when we're leaning. 0 = unit can't lean at all.
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float WeaponLeanOffset = 100.0f;

	// How close must the actual cover object be to a cover point. This is to avoid picking a cover point that doesn't provide meaningful cover.
	UPROPERTY(EditAnywhere, Category = Blackboard)
	float CoverPointMaxObjectHitDistance = 310.0f; // was 100.0f

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};



