// Fill out your copyright notice in the Description page of Project Settings.


#include "CheekyFPS/System/ApolloUserSettingsLibrary.h"

EGamepadType UApolloUserSettingsLibrary::GetPlayerGamepadType()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	EGamepadType GamepadType = InputSettings->CurrentGamepadType;
	return GamepadType;
}

bool UApolloUserSettingsLibrary::GetCrouchToggleSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bCrouchStats = InputSettings->bCrouchToggle;
	return bCrouchStats;
}

bool UApolloUserSettingsLibrary::GetSprintToggleSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bSprintStats = InputSettings->bSprintToggle;
	return bSprintStats;
}

bool UApolloUserSettingsLibrary::GetRunToggleSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bRunStats = InputSettings->bRunToggle;
	return false;
}

bool UApolloUserSettingsLibrary::GetWalkToggleSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bWalk = InputSettings->bWalkToggle;
	return bWalk;
}

bool UApolloUserSettingsLibrary::GetProneToggleSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bProne = InputSettings->bProneToggle;
	return bProne;
}

bool UApolloUserSettingsLibrary::GetMouseInvertXSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bMouseInvertX = InputSettings->bInvertMouseX;
	return bMouseInvertX;
}

bool UApolloUserSettingsLibrary::GetMouseInvertYSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bMouseInvertY = InputSettings->bInvertMouseY;
	return bMouseInvertY;
}

bool UApolloUserSettingsLibrary::GetGamepadInvertXSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bGamepadInvertX = InputSettings->bInvertGamepadLookX;
	return bGamepadInvertX;
}

bool UApolloUserSettingsLibrary::GetGamepadInvertYSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	bool bGamepadInvertY = InputSettings->bInvertGamepadLookY;
	return bGamepadInvertY;
}

float UApolloUserSettingsLibrary::GetMouseXSensitivitySetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fMouseXSens = InputSettings->MouseSensitivityX;
	return fMouseXSens;
}

float UApolloUserSettingsLibrary::GetMouseYSensitivitySetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fMouseYSens = InputSettings->MouseSensitivityY;
	return fMouseYSens;
}

float UApolloUserSettingsLibrary::GetGamepadXSensitivitySetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fGamepadXSens = InputSettings->GamepadSensitivityX;
	return fGamepadXSens;
}

float UApolloUserSettingsLibrary::GetGamepadYSensitivitySetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fGamepadYSens = InputSettings->GamepadSensitivityY;
	return fGamepadYSens;
}

float UApolloUserSettingsLibrary::GetMouseSmoothRateSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fMouseSmoothRate = InputSettings->MouseLookSmoothingRate;
	return fMouseSmoothRate;
}

float UApolloUserSettingsLibrary::GetGamepadSmoothRateSetting()
{
	const UPlayerInputSettings* InputSettings = GetDefault<UPlayerInputSettings>();
	float fGamepadSmoothRate = InputSettings->GamepadLookSmoothingRate;
	return fGamepadSmoothRate;
}

void UApolloUserSettingsLibrary::ResetToDefaults()
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->ResetToDefaultSettings();
}

void UApolloUserSettingsLibrary::SetPlayerGamepadType(EGamepadType NewGamepadType)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->CurrentGamepadType = NewGamepadType;
}

void UApolloUserSettingsLibrary::SetCrouchToggleSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bCrouchToggle = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetSprintToggleSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bSprintToggle = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetRunToggleSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bRunToggle = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetWalkToggleSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bWalkToggle = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetProneToggleSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bProneToggle = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetMouseInvertXSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bInvertMouseX = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetMouseInvertYSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bInvertMouseY = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetGamepadInvertXSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bInvertGamepadLookX = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetGamepadInvertYSetting(bool NewToggleStatus)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->bInvertGamepadLookY = NewToggleStatus;
}

void UApolloUserSettingsLibrary::SetMouseXSensitivitySetting(float NewSensitivityRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->MouseSensitivityX = NewSensitivityRate;
}

void UApolloUserSettingsLibrary::SetMouseYSensitivitySetting(float NewSensitivityRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->MouseSensitivityY = NewSensitivityRate;
}

void UApolloUserSettingsLibrary::SetGamepadXSensitivitySetting(float NewSensitivityRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->GamepadSensitivityX = NewSensitivityRate;
}

void UApolloUserSettingsLibrary::SetGamepadYSensitivitySetting(float NewSensitivityRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->GamepadSensitivityY = NewSensitivityRate;
}

void UApolloUserSettingsLibrary::SetMouseSmoothRateSetting(float NewSmoothRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->MouseLookSmoothingRate = NewSmoothRate;
}

void UApolloUserSettingsLibrary::SetGamepadSmoothRateSetting(float NewSmoothRate)
{
	UPlayerInputSettings* InputSettings = GetMutableDefault<UPlayerInputSettings>();
	InputSettings->GamepadLookSmoothingRate = NewSmoothRate;
}


