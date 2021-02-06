// Fill out your copyright notice in the Description page of Project Settings.


#include "CheekyFPS/System/ApolloPlayerSettings.h"

void UApolloPlayerSettings::ResetToDefaultSettings()
{
	bCrouchToggle = false;
	bSprintToggle = false;
	bRunToggle = false;
	bWalkToggle = false;
	bProneToggle = false;
	bInvertMouseX = false;
	bInvertMouseY = false;
	bInvertGamepadLookX = false;
	bInvertGamepadLookY = false;
	MouseSensitivityX = 1.0f;
	MouseSensitivityY = 1.0f;
	GamepadSensitivityX = 1.0f;
	GamepadSensitivityY = 1.0f;
	MouseLookSmoothingRate = 0.60f;
	GamepadLookSmoothingRate = 0.65f;
	CurrentGamepadType = EGamepadType::Xbox;
}
