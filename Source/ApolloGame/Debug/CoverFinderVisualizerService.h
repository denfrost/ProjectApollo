// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CoverFinderVisualizerService.generated.h"

/**
* Visualizes UCoverFinderService via the UCoverFinderVisData kept in the BB.
*/
UCLASS()
class APOLLOGAME_API UCoverFinderVisualizerService : public UBTService
{
	GENERATED_BODY()

private:
	const FName Key_VisData = FName("VisData");
	const FName Key_GenericDebug = FName("DrawDebug");
	const FName Key_UnitDebug = FName("bDebug");
	const FName Key_DebugVisDuration = FName("DebugVisDuration");

public:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};


