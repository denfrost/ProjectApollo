// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

//This is largely based on the Real Time Dynamic Cover System from David Nadaski - https://www.freecodecamp.org/news/real-time-dynamic-cover-system-in-unreal-engine-4-eddb554eaefb/

#pragma once

#include "CoreMinimal.h"

#include "CoverPointOctreeElement.h"
#include "Engine/World.h"

struct FCoverPointOctreeSemantics
{
	enum  { MaxElementsPerLeaf = 16 };
	enum  { MinInclusiveElementsPerNode = 7 };
	enum  { MaxNodeDepth = 12 };

	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
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