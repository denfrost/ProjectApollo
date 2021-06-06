// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

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
	GENERATED_BODY()

public:
	TSharedRef<FCoverPointOctreeData,ESPMode::ThreadSafe> Data;

	FBoxSphereBounds Bounds;

	FCoverPointOctreeElement()
		:	Data(new FCoverPointOctreeData()), Bounds()
	{}

	FCoverPointOctreeElement(FDTOCoverData CoverData)
		: Data(new FCoverPointOctreeData(CoverData)), Bounds(FSphere(CoverData.Location, 1.0f))
	{}

	FORCEINLINE bool IsEmpty() const
	{
		const FBox boundingBox = Bounds.GetBox();
		return boundingBox.IsValid == 0 || boundingBox.GetSize().IsNearlyZero();
	}

	FORCEINLINE UObject* GetOwner() const
	{
		return Data->CoverObject.Get();
	}
	
};
