// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "FindCover.h"

#include "AIController.h"
#include "ApolloGame/Debug/DebugArrow.h"
#include "ApolloGame/Debug/DebugPoint.h"
#include "ApolloGame/System/ApolloCoverSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

FVector UFindCover::GetPerpendicularVector(const FVector& Vector)
{
	return FVector(Vector.Y, -Vector.X, Vector.Z);
}

const void UFindCover::GetCoverPoints(
	TArray<FCoverPointOctreeElement>& OutCoverPoints,
	UWorld* World,
	const FVector& CharacterLocation,
	const FVector& EnemyLocation,
	UCoverFinderVisData& DebugData,
	const bool bUnitDebug) const
{
	const float minAttackRangeSquared = FMath::Square(MinAttackRange);

	// get cover points around the enemy that are inside our attack range
	const FBoxCenterAndExtent coverScanArea = FBoxCenterAndExtent(EnemyLocation, FVector(AttackRange * 0.5f));
	TArray<FCoverPointOctreeElement> coverPoints;
	if (UApolloCoverSystemLibrary::bShutdown)
		return;
	UApolloCoverSystemLibrary::GetInstance(World)->FindCoverPoints_Box(coverPoints, coverScanArea.GetBox());

	// filter out cover points that are too close to the enemy based on our min attack range, or already taken; populate a new array with the remaining, valid cover points only
	for (FCoverPointOctreeElement coverPoint : coverPoints)
		if (!coverPoint.Data->bIsTaken
			&& FVector::DistSquared(EnemyLocation, coverPoint.Data->Location) >= minAttackRangeSquared)
		{
			OutCoverPoints.Add(coverPoint);

#if DEBUG_RENDERING
			if (bUnitDebug)
				DebugData.DebugPoints.Add(FDebugPoint(coverPoint.Data->Location, FColor::Yellow, false));
#endif
		}
#if DEBUG_RENDERING
		else
			if (bUnitDebug)
				if (FVector::DistSquared(EnemyLocation, coverPoint.Data->Location) < minAttackRangeSquared)
					DebugData.DebugPoints.Add(FDebugPoint(coverPoint.Data->Location, FColor::Black, false));
#endif

	// sort cover points by their distance to our unit
	OutCoverPoints.Sort([CharacterLocation](const FCoverPointOctreeElement cp1, const FCoverPointOctreeElement cp2) {
		return FVector::DistSquared(CharacterLocation, cp1.Data->Location) < FVector::DistSquared(CharacterLocation, cp2.Data->Location);
	});
}



const bool UFindCover::CheckHitByLeaning(
	const FVector& CoverLocation,
	const AActor* OurUnit,
	const AActor* TargetEnemy,
	UWorld* World,
	UCoverFinderVisData& DebugData,
	bool bUnitDebug) const
{
	const FVector enemyLocation = TargetEnemy->GetActorLocation();

	FHitResult hit;
	FCollisionShape sphereColl;
	sphereColl.SetSphere(5.0f);
	FCollisionQueryParams collQueryParamsExclCharacter;
	collQueryParamsExclCharacter.AddIgnoredActor(OurUnit);
	collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_CheckHitByLeaning";

	// check leaning left and right
	for (int directionMultiplier = 1; directionMultiplier > -2; directionMultiplier -= 2)
	{
		// calculate our reach for when leaning out of cover
		const FVector coverEdge = enemyLocation - CoverLocation;
		const FVector coverEdgeDir = coverEdge.GetUnsafeNormal();
		FVector2D coverLean2D = FVector2D(GetPerpendicularVector(coverEdgeDir)) * directionMultiplier;
		coverLean2D *= WeaponLeanOffset;
		const FVector coverLean = FVector(CoverLocation.X + coverLean2D.X, CoverLocation.Y + coverLean2D.Y, CoverLocation.Z);

		// check if we can hit our target by leaning out of cover
		World->SweepSingleByChannel(hit, coverLean, enemyLocation, FQuat::Identity, ECollisionChannel::ECC_Camera, sphereColl, collQueryParamsExclCharacter);
		if (hit.GetActor() == TargetEnemy)
		{
#if DEBUG_RENDERING
			if (bUnitDebug)
			{
				DebugData.DebugArrows.Add(FDebugArrow(CoverLocation, coverLean, FColor::Orange, false));
				DebugData.DebugArrows.Add(FDebugArrow(coverLean, hit.Location, FColor::Orange, false));
			}
#endif

			return true;
		}

#if DEBUG_RENDERING
		if (bUnitDebug)
		{
			DebugData.DebugArrows.Add(FDebugArrow(CoverLocation, coverLean, FColor::Cyan, false));
			DebugData.DebugArrows.Add(FDebugArrow(coverLean, hit.Location, FColor::Cyan, false));
		}
#endif
	}

	// can't hit the enemy by leaning out of cover
	return false;
}

const bool UFindCover::EvaluateCoverPoint(
	const FCoverPointOctreeElement CoverPoint,
	const AActor* Character,
	const float CharEyeHeight,
	const AActor* TargetEnemy,
	const FVector& EnemyLocation,
	UWorld* World,
	UCoverFinderVisData& DebugData,
	bool bUnitDebug) const
{
	const FVector coverLocation = CoverPoint.Data->Location;
	const FVector coverLocationInEyeHeight = FVector(coverLocation.X, coverLocation.Y, coverLocation.Z - CoverPointGroundOffset + CharEyeHeight);

	FHitResult hit;
	FCollisionShape sphereColl;
	sphereColl.SetSphere(5.0f);
	FCollisionQueryParams collQueryParamsExclCharacter;
	collQueryParamsExclCharacter.AddIgnoredActor(Character);
	collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_EvaluateCoverPoint";

	// check if we can hit the enemy straight from the cover point. if we can, then the cover point is no good
	if (!World->SweepSingleByChannel(hit, coverLocationInEyeHeight, EnemyLocation, FQuat::Identity, ECollisionChannel::ECC_Camera, sphereColl, collQueryParamsExclCharacter))
		return false;

	// if the cover point is behind a shield then we shouldn't do any leaning checks, however we must be able to hit the enemy directly and through the shield
	// for this, we will need a second raycast to determine if we're hitting the shield, which has a different collision response than regular objects
	const AActor* hitActor = hit.GetActor();
	if (CoverPoint.Data->bIsForceField // cover is a force field (shield)
		&& hitActor == TargetEnemy) // should be able to hit the enemy directly
	{
		collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_HitShieldFromCover";
		FHitResult shieldHit;
		bool bHitShield = World->SweepSingleByChannel(shieldHit, coverLocationInEyeHeight, EnemyLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, sphereColl, collQueryParamsExclCharacter);
		if (bHitShield // we must hit the shield
			&& shieldHit.Distance <= CoverPointMaxObjectHitDistance) // cover point and cover object must be close to one another
			return true;

#if DEBUG_RENDERING
		if (bUnitDebug)
			if (!bHitShield)
				DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Red, false));
			else if (shieldHit.Distance > CoverPointMaxObjectHitDistance)
				DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Black, false));
#endif
	}
	// if the cover point is not behind a shield then check if we can hit the enemy by leaning out of cover
	else if (!CoverPoint.Data->bIsForceField // cover is not a force field (shield)
		&& hit.Distance <= CoverPointMaxObjectHitDistance // cover point and cover object must be close to one another
		&& hitActor != TargetEnemy // shouldn't be able to hit the enemy directly
		&& !hitActor->IsA<APawn>() // can't hide behind other units, for now
		&& CheckHitByLeaning(coverLocationInEyeHeight, Character, TargetEnemy, World, DebugData, bUnitDebug)) // we should only be able to hit the enemy by leaning out of cover
		return true;

#if DEBUG_RENDERING
	if (bUnitDebug && !CoverPoint.Data->bIsForceField)
		if (hitActor == TargetEnemy)
			DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Purple, false));
		else if (hit.Distance > CoverPointMaxObjectHitDistance)
			DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Blue, false));
#endif

	return false;
}

const bool UFindCover::CheckHitByLeaning(const FVector& CoverLocation, const ACharacter* OurUnit,
	const AActor* TargetEnemy, UWorld* World, UCoverFinderVisData& DebugData, const bool bUnitDebug) const
{
	const FVector enemyLocation = TargetEnemy->GetActorLocation();

	FHitResult hit;
	FCollisionShape sphereColl;
	sphereColl.SetSphere(5.0f);
	FCollisionQueryParams collQueryParamsExclCharacter;
	collQueryParamsExclCharacter.AddIgnoredActor(OurUnit);
	collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_CheckHitByLeaning";

	// check leaning left and right
	for (int directionMultiplier = 1; directionMultiplier > -2; directionMultiplier -= 2)
	{
		// calculate our reach for when leaning out of cover
		const FVector coverEdge = enemyLocation - CoverLocation;
		const FVector coverEdgeDir = coverEdge.GetUnsafeNormal();
		FVector2D coverLean2D = FVector2D(GetPerpendicularVector(coverEdgeDir)) * directionMultiplier;
		coverLean2D *= WeaponLeanOffset;
		const FVector coverLean = FVector(CoverLocation.X + coverLean2D.X, CoverLocation.Y + coverLean2D.Y, CoverLocation.Z);

		// check if we can hit our target by leaning out of cover
		World->SweepSingleByChannel(hit, coverLean, enemyLocation, FQuat::Identity, ECollisionChannel::ECC_Camera, sphereColl, collQueryParamsExclCharacter);
		if (hit.GetActor() == TargetEnemy)
		{
#if DEBUG_RENDERING
			if (bUnitDebug)
			{
				DebugData.DebugArrows.Add(FDebugArrow(CoverLocation, coverLean, FColor::Orange, false));
				DebugData.DebugArrows.Add(FDebugArrow(coverLean, hit.Location, FColor::Orange, false));
			}
#endif

			return true;
		}

#if DEBUG_RENDERING
		if (bUnitDebug)
		{
			DebugData.DebugArrows.Add(FDebugArrow(CoverLocation, coverLean, FColor::Cyan, false));
			DebugData.DebugArrows.Add(FDebugArrow(coverLean, hit.Location, FColor::Cyan, false));
		}
#endif
	}

	// can't hit the enemy by leaning out of cover
	return false;
}

const bool UFindCover::EvaluateCoverPoint(const FCoverPointOctreeElement CoverPoint, const ACharacter* Character,
                                          const float CharEyeHeight, const AActor* TargetEnemy, const FVector& EnemyLocation, UWorld* World,
                                          UCoverFinderVisData& DebugData, const bool bUnitDebug) const
{
	const FVector coverLocation = CoverPoint.Data->Location;
	const FVector coverLocationInEyeHeight = FVector(coverLocation.X, coverLocation.Y, coverLocation.Z - CoverPointGroundOffset + CharEyeHeight);

	FHitResult hit;
	FCollisionShape sphereColl;
	sphereColl.SetSphere(5.0f);
	FCollisionQueryParams collQueryParamsExclCharacter;
	collQueryParamsExclCharacter.AddIgnoredActor(Character);
	collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_EvaluateCoverPoint";

	// check if we can hit the enemy straight from the cover point. if we can, then the cover point is no good
	if (!World->SweepSingleByChannel(hit, coverLocationInEyeHeight, EnemyLocation, FQuat::Identity, ECollisionChannel::ECC_Camera, sphereColl, collQueryParamsExclCharacter))
		return false;

	// if the cover point is behind a shield then we shouldn't do any leaning checks, however we must be able to hit the enemy directly and through the shield
	// for this, we will need a second raycast to determine if we're hitting the shield, which has a different collision response than regular objects
	const AActor* hitActor = hit.GetActor();
	if (CoverPoint.Data->bIsForceField // cover is a force field (shield)
		&& hitActor == TargetEnemy) // should be able to hit the enemy directly
	{
		collQueryParamsExclCharacter.TraceTag = "CoverPointFinder_HitShieldFromCover";
		FHitResult shieldHit;
		bool bHitShield = World->SweepSingleByChannel(shieldHit, coverLocationInEyeHeight, EnemyLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, sphereColl, collQueryParamsExclCharacter);
		if (bHitShield // we must hit the shield
			&& shieldHit.Distance <= CoverPointMaxObjectHitDistance) // cover point and cover object must be close to one another
			return true;

#if DEBUG_RENDERING
		if (bUnitDebug)
			if (!bHitShield)
				DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Red, false));
			else if (shieldHit.Distance > CoverPointMaxObjectHitDistance)
				DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Black, false));
#endif
	}
	// if the cover point is not behind a shield then check if we can hit the enemy by leaning out of cover
	else if (!CoverPoint.Data->bIsForceField // cover is not a force field (shield)
		&& hit.Distance <= CoverPointMaxObjectHitDistance // cover point and cover object must be close to one another
		&& hitActor != TargetEnemy // shouldn't be able to hit the enemy directly
		&& !hitActor->IsA<APawn>() // can't hide behind other units, for now
		&& CheckHitByLeaning(coverLocationInEyeHeight, Character, TargetEnemy, World, DebugData, bUnitDebug)) // we should only be able to hit the enemy by leaning out of cover
		return true;

#if DEBUG_RENDERING
	if (bUnitDebug && !CoverPoint.Data->bIsForceField)
		if (hitActor == TargetEnemy)
			DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Purple, false));
		else if (hit.Distance > CoverPointMaxObjectHitDistance)
			DebugData.DebugArrows.Add(FDebugArrow(coverLocationInEyeHeight, EnemyLocation, FColor::Blue, false));
#endif

	return false;
}

EBTNodeResult::Type UFindCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// profiling
	SCOPE_CYCLE_COUNTER(STAT_FindCover);
	INC_DWORD_STAT(STAT_FindCoverHistoricalCount);
	SCOPE_SECONDS_ACCUMULATOR(STAT_FindCoverTotalTimeSpent);

	UWorld* World = GetWorld();
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	const AActor* TargetEnemy = Cast<AActor>(BlackBoardComp->GetValue<UBlackboardKeyType_Object>(Enemy.SelectedKeyName));
	const ACharacter* Character = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
	const FVector characterLocation = Character->GetActorLocation();
	const FVector enemyLocation = TargetEnemy->GetActorLocation();
	UCoverFinderVisData* debugData = NewObject<UCoverFinderVisData>(this);
	const bool bDrawDebug =
#if DEBUG_RENDERING
		BlackBoardComp->GetValueAsBool(DrawDebug.SelectedKeyName);
#else
		false;
#endif
	const bool bUnitDebug =
#if DEBUG_RENDERING
		BlackBoardComp->GetValueAsBool(FName("bDebug"));
#else
		false;
#endif

#if DEBUG_RENDERING
	BlackBoardComp->SetValueAsObject(Key_VisData, debugData);

	// draw an arrow from our character to the enemy, in red, if the generic debug flag is set
	if (bDrawDebug)
		debugData->DebugArrows.Add(FDebugArrow(characterLocation, enemyLocation, FColor::Red, true));
#endif

	// release the former cover point, if any
	if (BlackBoardComp->IsVectorValueSet(OutputVector.SelectedKeyName))
	{
		FVector FormerCover = BlackBoardComp->GetValueAsVector(OutputVector.SelectedKeyName);

		if (UApolloCoverSystemLibrary::bShutdown)
			return EBTNodeResult::Type::Failed;
		UApolloCoverSystemLibrary::GetInstance(World)->ReleaseCover(FormerCover);
	}

	// get the cover points
	TArray<FCoverPointOctreeElement> coverPoints;
	GetCoverPoints(coverPoints, World, characterLocation, enemyLocation, *debugData, bUnitDebug);

	// get navigation data
	const UNavigationSystemV1* Navsys = UNavigationSystemV1::GetCurrent(GetWorld());
	const ANavigationData* NavData = Navsys->GetDefaultNavDataInstance();

	// calculate the character's standing and crouched eye height offsets
	const float capsuleHalfHeight = Character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const float charEyeHeightStanding = capsuleHalfHeight + Character->BaseEyeHeight;
	const float charEyeHeightCrouched = capsuleHalfHeight + Character->CrouchedEyeHeight;

	// find the first adequate cover point
	for (const FCoverPointOctreeElement coverPoint : coverPoints)
	{
		const FVector coverLocation = coverPoint.Data->Location;
		
		// our unit must be able to reach the cover point
		// TODO: this is a relatively expensive operation, consider implementing an async query instead?
		if (!Navsys->TestPathSync(FPathFindingQuery(Character, *NavData, characterLocation, coverLocation)))
		{
#if DEBUG_RENDERING
			if (bUnitDebug)
				debugData->DebugPoints.Add(FDebugPoint(coverPoint.Data->Location, FColor::Red, false));
#endif

			continue;
		}

		// check from a standing position and if that fails then from a crouched one
		bool bFoundCover = EvaluateCoverPoint(coverPoint, Character, charEyeHeightStanding, TargetEnemy, enemyLocation, World, *debugData, bUnitDebug)
			|| EvaluateCoverPoint(coverPoint, Character, charEyeHeightCrouched, TargetEnemy, enemyLocation, World, *debugData, bUnitDebug);

		if (bFoundCover)
		{
			// mark the cover point as taken
			if (UApolloCoverSystemLibrary::bShutdown)
				return EBTNodeResult::Type::Failed;
			UApolloCoverSystemLibrary::GetInstance(World)->HoldCover(coverLocation);

			// draw an arrow from the cover point to the enemy, in green (success), if the unit debug flag is set
#if DEBUG_RENDERING
			if (bUnitDebug)
				debugData->DebugArrows.Add(FDebugArrow(coverLocation, enemyLocation, FColor::Green, false));
#endif

			// set the cover location in the BB
			BlackBoardComp->SetValueAsVector(OutputVector.SelectedKeyName, coverLocation);
			return EBTNodeResult::Type::Succeeded;
		}
	}

	// draw a red marker above units that can't find any cover
#if DEBUG_RENDERING
	if (bDrawDebug)
		debugData->DebugPoints.Add(FDebugPoint(characterLocation + FVector(0.0f, 0.0f, 200.0f), FColor::Red, true));
#endif

	// no cover found: unset the cover location in the BB
	BlackBoardComp->ClearValue(OutputVector.SelectedKeyName);
	return EBTNodeResult::Type::Failed;
}
