// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "CoverOctree.h"


TCoverOctree::TCoverOctree()
	: TOctree2<FCoverPointOctreeElement, FCoverPointOctreeSemantics>()
{}

TCoverOctree::TCoverOctree(const FVector& Origin, float Radius)
	: TOctree2<FCoverPointOctreeElement, FCoverPointOctreeSemantics>(Origin, Radius)
{}

TCoverOctree::~TCoverOctree()
{}

bool TCoverOctree::AddCoverPoint(FDTOCoverData CoverData, const float DuplicateRadius)
{
	//Check if any cover points are close enough - stop if so
	if(AnyCoverPointsWithinBounds(FBoxCenterAndExtent(CoverData.Location, FVector(DuplicateRadius))))
	{
		return false;
	}
	AddElement(FCoverPointOctreeElement(CoverData));
	return true;
}

bool TCoverOctree::AnyCoverPointsWithinBounds(const FBoxCenterAndExtent& QueryBox) const
{
	bool Result = false;
	FindFirstElementWithBoundsTest(QueryBox, [&Result](const FCoverPointOctreeElement& CoverPoint) { Result = true; return true; });
	return Result;
}

void TCoverOctree::FindCoverPoints_Box(TArray<FCoverPointOctreeElement>& OutCoverPoints, const FBox& QueryBox) const
{
	FindElementsWithBoundsTest(QueryBox, [&OutCoverPoints](const FCoverPointOctreeElement& CoverPoint){OutCoverPoints.Add(CoverPoint); });
}

void TCoverOctree::FindCoverPoints_Sphere(TArray<FCoverPointOctreeElement>& OutCoverPoints,
	const FSphere& QuerySphere) const
{
	const FBoxCenterAndExtent& boxFromSphere = FBoxCenterAndExtent(QuerySphere.Center, FVector(QuerySphere.W));
	FindElementsWithBoundsTest(boxFromSphere, [&OutCoverPoints, &QuerySphere](const FCoverPointOctreeElement& CoverPoint)
	{
		//Check if cover point is inside the supplied sphere's radius, now that we've estimated with a box query
		if(QuerySphere.Intersects(CoverPoint.Bounds.GetSphere()))
		{
			OutCoverPoints.Add(CoverPoint);
		}
	});
	
}

void TCoverOctree::RemoveElement(FOctreeElementId2 ElementID)
{
	if(!ElementID.IsValidId())
	{
		return;
	}
	static_cast<TOctree2*>(this)->RemoveElement(ElementID);

}

bool TCoverOctree::HoldCover(FOctreeElementId2 ElementID)
{
	if(!ElementID.IsValidId())
	{
		return false;
	}
	FCoverPointOctreeElement coverElement = GetElementById(ElementID);
	return HoldCover(coverElement);
}

bool TCoverOctree::HoldCover(FCoverPointOctreeElement Element)
{
	if(Element.Data->bIsTaken)
	{
		return false;
	}
	Element.Data->bIsTaken = true;
	return true;
}

bool TCoverOctree::ReleaseCover(FOctreeElementId2 ElementID)
{
	if(!ElementID.IsValidId())
	{
		return false;
	}
	FCoverPointOctreeElement coverElement = GetElementById(ElementID);
	return ReleaseCover(coverElement);
}

bool TCoverOctree::ReleaseCover(FCoverPointOctreeElement Element)
{
	if(!Element.Data->bIsTaken)
	{
		return false;
	}
	Element.Data->bIsTaken = false;
	return true;
}


