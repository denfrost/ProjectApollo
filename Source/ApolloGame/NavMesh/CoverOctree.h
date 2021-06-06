// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "Math/GenericOctreePublic.h"
#include "Math/GenericOctree.h"
#include "GameFramework/Actor.h"
#include "CoverPointOctreeElement.h"
#include "CoverPointOctreeSemantics.h"

/**
* Octree for storing cover points. This is not thread safe, please use the CoverSystem Library for modifications.
*/

class TCoverOctree : public TOctree2<FCoverPointOctreeElement, FCoverPointOctreeSemantics>, public TSharedFromThis<TCoverOctree, ESPMode::ThreadSafe>
{
public:
	//Constructor
	TCoverOctree();

	TCoverOctree(const FVector& Origin, float Radius);

	//Destructor
	~TCoverOctree();

	//Adds a cover point entry to octree
	bool AddCoverPoint(FDTOCoverData CoverData, const float DuplicateRadius);

	//Checks if any cover points are within bounds
	//@param const FBoxCenterAndExtent - supplied bounds
	bool AnyCoverPointsWithinBounds(const FBoxCenterAndExtent& QueryBox) const;

	//Finds cover points that intersect the supplied box
	void FindCoverPoints_Box(TArray<FCoverPointOctreeElement>& OutCoverPoints, const FBox& QueryBox) const;

	//Finds cover points that intersect the supplied sphere
	void FindCoverPoints_Sphere(TArray<FCoverPointOctreeElement>& OutCoverPoints, const FSphere& QuerySphere) const;

	//Won't crash the game if ElementID is invalid, this method will hide the base class method as it's not virtual
	void RemoveElement(FOctreeElementId2 ElementID);

	//Mark the cover at the supplied location as taken
	//Returns true if cover wasn't taken, false if it was or if the cover no longer exists
	bool HoldCover(FOctreeElementId2 ElementID);
	bool HoldCover(FCoverPointOctreeElement Element);

	//Releases a cover that was taken
	//Returns true if cover wasn't taken, false if it was or if the cover no longer exists
	bool ReleaseCover(FOctreeElementId2 ElementID);
	bool ReleaseCover(FCoverPointOctreeElement Element);
	
};