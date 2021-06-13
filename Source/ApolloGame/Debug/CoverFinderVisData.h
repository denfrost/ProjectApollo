// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "DebugPoint.h"
#include "DebugArrow.h"
#include "CoverFinderVisData.generated.h"

/**
* Visualization data for debugging the cover finder.
*/
UCLASS()
class APOLLOGAME_API UCoverFinderVisData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FDebugPoint> DebugPoints;

	UPROPERTY()
	TArray<FDebugArrow> DebugArrows;
};
