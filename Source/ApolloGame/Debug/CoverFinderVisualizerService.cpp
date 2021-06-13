// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "CoverFinderVisualizerService.h"

#include "CoverFinderVisData.h"
#include "BehaviorTree/BlackboardComponent.h"
#if DEBUG_RENDERING
#include "DrawDebugHelpers.h"
#endif

void UCoverFinderVisualizerService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

#if DEBUG_RENDERING
	UBlackboardComponent* blackBoardComp = OwnerComp.GetBlackboardComponent();
	const bool bGenericDebug = blackBoardComp->GetValueAsBool(Key_GenericDebug);
	const bool bUnitDebug = blackBoardComp->GetValueAsBool(Key_UnitDebug);

	if (!bGenericDebug && !bUnitDebug)
		return;

	const float debugVisDuration = blackBoardComp->GetValueAsFloat(Key_DebugVisDuration);

	UWorld* world = GetWorld();
	UCoverFinderVisData* visData = Cast<UCoverFinderVisData>(blackBoardComp->GetValueAsObject(Key_VisData));
	if (!IsValid(visData))
		return;

	for (FDebugPoint debugPoint : visData->DebugPoints)
		if ((debugPoint.bGenericOrUnitDebugData && bGenericDebug)
			|| (!debugPoint.bGenericOrUnitDebugData && bUnitDebug))
			DrawDebugSphere(world, debugPoint.Location, 20.0f, 4, debugPoint.Color, false, debugVisDuration);

	for (FDebugArrow debugArrow : visData->DebugArrows)
		if ((debugArrow.bGenericOrUnitDebugData && bGenericDebug)
			|| (!debugArrow.bGenericOrUnitDebugData && bUnitDebug))
			DrawDebugDirectionalArrow(world, debugArrow.Start, debugArrow.End, 50.0f, debugArrow.Color, false,
			                          debugVisDuration, 0, 2.0f);
#endif
}
