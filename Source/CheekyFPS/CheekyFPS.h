// Fill out your copyright notice in the Description page of Project Settings.

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

