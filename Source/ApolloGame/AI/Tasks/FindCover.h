// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"

#include "ApolloGame/Debug/CoverFinderVisData.h"
#include "ApolloGame/NavMesh/CoverPointOctreeData.h"
#include "ApolloGame/NavMesh/CoverPointOctreeElement.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindCover.generated.h"

/**
* Finds suitable cover by looking around a unit in a full sphere.
*/
UCLASS()
class APOLLOGAME_API UFindCover : public UBTTaskNode
{
	GENERATED_BODY()

private:
	
	static FVector GetPerpendicularVector(const FVector& Vector);

	//Should be the same as the one defined in the Cover System
	const float CoverPointGroundOffset = 10.0f;

	const FName Key_VisData = FName("VisData");

	// //Gather, filter and sort cover points
	const void GetCoverPoints(TArray<FCoverPointOctreeElement>& OutCoverPoints, UWorld* World, const FVector& PawnLocation, const FVector& EnemyLocation,UCoverFinderVisData& DebugData,const bool bUnitDebug = false) const;
	const bool CheckHitByLeaning(const FVector& CoverLocation, const AActor* OurUnit, const AActor* TargetEnemy,
	                             UWorld* World, UCoverFinderVisData& DebugData, bool bUnitDebug) const;
	const bool EvaluateCoverPoint(FCoverPointOctreeElement CoverPoint, const AActor* Character, float CharEyeHeight,
	                              const AActor* TargetEnemy, const FVector& EnemyLocation, UWorld* World,
	                              UCoverFinderVisData& DebugData, bool bUnitDebug) const;
	// Checks if there's clear line of sight to the enemy when leaning to the right.
	const bool CheckHitByLeaning(
		const FVector& CoverLocation,
		const ACharacter* OurUnit,
		const AActor* TargetEnemy,
		UWorld* World,
		UCoverFinderVisData& DebugData,
		const bool bUnitDebug = false) const;

	const bool EvaluateCoverPoint(
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

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
