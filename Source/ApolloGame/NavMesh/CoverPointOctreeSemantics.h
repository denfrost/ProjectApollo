// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"

#include "CoverPointOctreeElement.h"
#include "Engine/World.h"

struct FCoverPointOctreeSemantics
{
	enum  { MaxElementsPerLeaf = 16 };
	enum  { MinInclusiveElementsPerNode = 7 };
	enum  { MaxNodeDepth = 12 };

	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	FORCEINLINE static const FBoxSphereBounds GetBoundingBox(const FCoverPointOctreeElement& Element)
	{
		return Element.Bounds;
	}

	FORCEINLINE static bool AreElementsEqual(const FCoverPointOctreeElement& A, const FCoverPointOctreeElement& B)
	{
		//TODO: Review this when introducing new properties to FCoverPointData
		return A.Bounds == B.Bounds;
	}

	static void SetElementId(const FCoverPointOctreeElement& Element, FOctreeElementId2 ID);
};