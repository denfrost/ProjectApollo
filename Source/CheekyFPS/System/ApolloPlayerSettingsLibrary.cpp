// Fill out your copyright notice in the Description page of Project Settings.


#include "CheekyFPS/System/ApolloPlayerSettingsLibrary.h"

EGamepadType UApolloPlayerSettingsLibrary::GetPlayerGamepadType()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	EGamepadType GamepadType = InputSettings->CurrentGamepadType;
	return GamepadType;
}

bool UApolloPlayerSettingsLibrary::GetCrouchToggleSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bCrouchStats = InputSettings->bCrouchToggle;
	return bCrouchStats;
}

bool UApolloPlayerSettingsLibrary::GetSprintToggleSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bSprintStats = InputSettings->bSprintToggle;
	return bSprintStats;
}

bool UApolloPlayerSettingsLibrary::GetRunToggleSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bRunStats = InputSettings->bRunToggle;
	return false;
}

bool UApolloPlayerSettingsLibrary::GetWalkToggleSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bWalk = InputSettings->bWalkToggle;
	return bWalk;
}

bool UApolloPlayerSettingsLibrary::GetProneToggleSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bProne = InputSettings->bProneToggle;
	return bProne;
}

bool UApolloPlayerSettingsLibrary::GetMouseInvertXSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bMouseInvertX = InputSettings->bInvertMouseX;
	return bMouseInvertX;
}

bool UApolloPlayerSettingsLibrary::GetMouseInvertYSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bMouseInvertY = InputSettings->bInvertMouseY;
	return bMouseInvertY;
}

bool UApolloPlayerSettingsLibrary::GetGamepadInvertXSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bGamepadInvertX = InputSettings->bInvertGamepadLookX;
	return bGamepadInvertX;
}

bool UApolloPlayerSettingsLibrary::GetGamepadInvertYSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	bool bGamepadInvertY = InputSettings->bInvertGamepadLookY;
	return bGamepadInvertY;
}

float UApolloPlayerSettingsLibrary::GetMouseXSensitivitySetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fMouseXSens = InputSettings->MouseSensitivityX;
	return fMouseXSens;
}

float UApolloPlayerSettingsLibrary::GetMouseYSensitivitySetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fMouseYSens = InputSettings->MouseSensitivityY;
	return fMouseYSens;
}

float UApolloPlayerSettingsLibrary::GetGamepadXSensitivitySetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fGamepadXSens = InputSettings->GamepadSensitivityX;
	return fGamepadXSens;
}

float UApolloPlayerSettingsLibrary::GetGamepadYSensitivitySetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fGamepadYSens = InputSettings->GamepadSensitivityY;
	return fGamepadYSens;
}

float UApolloPlayerSettingsLibrary::GetMouseSmoothRateSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fMouseSmoothRate = InputSettings->MouseLookSmoothingRate;
	return fMouseSmoothRate;
}

float UApolloPlayerSettingsLibrary::GetGamepadSmoothRateSetting()
{
	const UApolloPlayerSettings* InputSettings = GetDefault<UApolloPlayerSettings>();
	float fGamepadSmoothRate = InputSettings->GamepadLookSmoothingRate;
	return fGamepadSmoothRate;
}

void UApolloPlayerSettingsLibrary::ResetToDefaults()
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->ResetToDefaultSettings();
}

void UApolloPlayerSettingsLibrary::SetPlayerGamepadType(EGamepadType NewGamepadType)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->CurrentGamepadType = NewGamepadType;
}

void UApolloPlayerSettingsLibrary::SetCrouchToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bCrouchToggle = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetSprintToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bSprintToggle = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetRunToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bRunToggle = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetWalkToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bWalkToggle = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetProneToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bProneToggle = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetMouseInvertXSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bInvertMouseX = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetMouseInvertYSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bInvertMouseY = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetGamepadInvertXSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bInvertGamepadLookX = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetGamepadInvertYSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->bInvertGamepadLookY = NewToggleStatus;
}

void UApolloPlayerSettingsLibrary::SetMouseXSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->MouseSensitivityX = NewSensitivityRate;
}

void UApolloPlayerSettingsLibrary::SetMouseYSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->MouseSensitivityY = NewSensitivityRate;
}

void UApolloPlayerSettingsLibrary::SetGamepadXSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->GamepadSensitivityX = NewSensitivityRate;
}

void UApolloPlayerSettingsLibrary::SetGamepadYSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->GamepadSensitivityY = NewSensitivityRate;
}

void UApolloPlayerSettingsLibrary::SetMouseSmoothRateSetting(float NewSmoothRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->MouseLookSmoothingRate = NewSmoothRate;
}

void UApolloPlayerSettingsLibrary::SetGamepadSmoothRateSetting(float NewSmoothRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->GamepadLookSmoothingRate = NewSmoothRate;
}

