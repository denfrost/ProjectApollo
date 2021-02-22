// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ApolloPlayerSettings.h"

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
	SaveConfig();
}

void UApolloPlayerSettings::ResetMouseSettings()
{
	bInvertMouseX = false;
	bInvertMouseY = false;
	MouseSensitivityX = 1.0f;
	MouseSensitivityY = 1.0f;
	MouseLookSmoothingRate = 0.60f;
	SaveConfig();
}

void UApolloPlayerSettings::ResetGamepadSettings()
{
	bInvertGamepadLookX = false;
	bInvertGamepadLookY = false;
	GamepadSensitivityX = 1.0f;
	GamepadSensitivityY = 1.0f;
	GamepadLookSmoothingRate = 0.65f;
	CurrentGamepadType = EGamepadType::Xbox;
	SaveConfig();
}

void UApolloPlayerSettings::ResetToggleSettings()
{
	bCrouchToggle = false;
	bSprintToggle = false;
	bRunToggle = false;
	bWalkToggle = false;
	bProneToggle = false;
	SaveConfig();
}

void UApolloPlayerSettings::SetCrouchToggleSetting(bool bShouldToggle)
{
	bCrouchToggle = bShouldToggle;
	SaveConfig();
}

void UApolloPlayerSettings::SetSprintToggleSetting(bool bShouldToggle)
{
	bSprintToggle = bShouldToggle;
	SaveConfig();
}

void UApolloPlayerSettings::SetRunToggleSetting(bool bShouldToggle)
{
	bRunToggle = bShouldToggle;
	SaveConfig();
}

void UApolloPlayerSettings::SetWalkToggleSetting(bool bShouldToggle)
{
	bWalkToggle = bShouldToggle;
	SaveConfig();
}

void UApolloPlayerSettings::SetProneToggleSetting(bool bShouldToggle)
{
	bProneToggle = bShouldToggle;
	SaveConfig();
}

void UApolloPlayerSettings::SetMouseXSensitivity(float NewSensitivityRate)
{
	MouseSensitivityX = NewSensitivityRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetMouseYSensitivity(float NewSensitivityRate)
{
	MouseSensitivityY = NewSensitivityRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetMouseSmoothing(float NewSmoothingRate)
{
	MouseLookSmoothingRate = NewSmoothingRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetMouseXInvertSetting(bool bShouldInvert)
{
	bInvertMouseY = bShouldInvert;
	SaveConfig();
}

void UApolloPlayerSettings::SetMouseYInvertSetting(bool bShouldInvert)
{
	bInvertMouseY = bShouldInvert;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadXSensitivity(float NewSensitivityRate)
{
	GamepadSensitivityX = NewSensitivityRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadYSensitivity(float NewSensitivityRate)
{
	GamepadSensitivityY = NewSensitivityRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadXInvertSetting(bool bShouldInvert)
{
	bInvertGamepadLookX = bShouldInvert;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadYInvertSetting(bool bShouldInvert)
{
	bInvertGamepadLookY = bShouldInvert;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadSmoothing(float NewSmoothingRate)
{
	MouseLookSmoothingRate = NewSmoothingRate;
	SaveConfig();
}

void UApolloPlayerSettings::SetGamepadTypeSetting(EGamepadType NewGamepadType)
{
	CurrentGamepadType = NewGamepadType;
	SaveConfig();
}

void UApolloPlayerSettings::SetRTGISetting(bool bEnableSetting)
{
	bEnableRTGI = bEnableSetting;
}

void UApolloPlayerSettings::SetRTShadows(bool bEnableSetting)
{
	bEnableRTShadows = bEnableSetting;
}

void UApolloPlayerSettings::SetRTAOSetting(bool bEnableSetting)
{
	bEnableRTAO = bEnableSetting;
}

void UApolloPlayerSettings::SetRTReflectionsSetting(bool bEnableSetting)
{
	bEnableRTReflections = bEnableSetting;
}

void UApolloPlayerSettings::SetRTTranslucencySetting(bool bEnableSetting)
{
	bEnableRTTranslucency = bEnableSetting;
}
