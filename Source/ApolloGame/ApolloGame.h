// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "EngineMinimal.h"

UENUM(BlueprintType)
enum class EGamepadType : uint8
{
	None,
	Xbox,
	DS3 UMETA(DisplayName = "Dualshock 3"),
	DS4 UMETA(DisplayName = "Dualshock 4"),
	DS5 UMETA(DisplayName = "DualSense"),
	SwitchPro UMETA(DisplayName = "Switch Pro"),
	Steam UMETA(DisplayName = "Steam Controller"),
};

UENUM(BlueprintType)
enum class EGameDifficultySetting : uint8
{
	Beginner,
	Easy,
	Medium,
	Hard,
	VeryHard UMETA(DisplayName = "Very Hard"),
	Extreme UMETA(DisplayName = "True Agent")

};



