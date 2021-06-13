// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"

#include "CoverPointOctreeData.h"
#include "GameFramework/Actor.h"
#include "Math/GenericOctree.h"
#include "Math/GenericOctreePublic.h"
#include "ApolloGame/System/DTOCoverData.h"
#include "CoverPointOctreeElement.generated.h"

USTRUCT(BlueprintType)
struct FCoverPointOctreeElement
{
	GENERATED_USTRUCT_BODY()

public:
	TSharedRef<FCoverPointOctreeData,ESPMode::ThreadSafe> Data;

	FBoxSphereBounds Bounds;

	FCoverPointOctreeElement()
		:	Data(new FCoverPointOctreeData()), Bounds()
	{}

	explicit FCoverPointOctreeElement(FDTOCoverData& CoverData)
		: Data(new FCoverPointOctreeData(CoverData)), Bounds(FSphere(CoverData.Location, 1.0f))
	{}

	FORCEINLINE bool IsEmpty() const
	{
		const FBox BoundingBox = Bounds.GetBox();
		return BoundingBox.IsValid == 0 || BoundingBox.GetSize().IsNearlyZero();
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Data->CoverObject.Get();
	}
	
};
