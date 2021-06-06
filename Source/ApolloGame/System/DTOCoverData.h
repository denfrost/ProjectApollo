// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"

/**
* DTO for FCoverPointOctreeData
*/
struct FDTOCoverData
{
public:
	AActor* CoverObject;
	FVector Location;
	bool bIsForceField;

	FDTOCoverData()
		: CoverObject(), Location(), bIsForceField()
	{}

	FDTOCoverData(AActor* _CoverObject, FVector _Location, bool _bForceField)
		: CoverObject(_CoverObject), Location(_Location), bIsForceField(_bForceField)
	{}
};
