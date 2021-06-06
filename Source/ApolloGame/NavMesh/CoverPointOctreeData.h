// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "ApolloGame/System/DTOCoverData.h"

//Shared pointer type that is set to be thread safe
struct FCoverPointOctreeData : public TSharedFromThis<FCoverPointOctreeData, ESPMode::ThreadSafe>
{
public:

	//Location of the generated cover point - marked const
	const FVector Location;

	//true if Actor is a force field, meaning units can walk through but projectiles are blocked
	const bool bIsForceField;

	//Object that generated this cover point
	const TWeakObjectPtr<AActor> CoverObject;

	//Whether the cover point is taken by a pawn
	bool bIsTaken = false;

	//Default constructor

	FCoverPointOctreeData()
		: Location(), bIsForceField(false), CoverObject(), bIsTaken(false)
	{}

	FCoverPointOctreeData(FDTOCoverData CoverData)
		: Location(CoverData.Location), bIsForceField(CoverData.bIsForceField), CoverObject(CoverData.CoverObject), bIsTaken(false)
	{}
	
};
