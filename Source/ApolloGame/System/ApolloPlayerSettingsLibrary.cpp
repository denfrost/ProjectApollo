// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloPlayerSettingsLibrary.h"
#include "InputCore/Classes/InputCoreTypes.h"
#include "UINavigation/Public/Data/InputIconMapping.h"
#include <Engine/DataTable.h>

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

void UApolloPlayerSettingsLibrary::ResetAllSettingsToDefault()
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->ResetToDefaultSettings();
}

void UApolloPlayerSettingsLibrary::ResetGameSettingsToDefault()
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->ResetMouseSettings();
	InputSettings->ResetGamepadSettings();
	InputSettings->ResetToggleSettings();
}

FName UApolloPlayerSettingsLibrary::GetKeyName(FKey KeyPressed)
{
	return KeyPressed.GetFName();
}

void UApolloPlayerSettingsLibrary::SetRTGlobalIlluminationSetting(bool bEnableSetting)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRTGISetting(bEnableSetting);
}

void UApolloPlayerSettingsLibrary::SetRTShadowsSetting(bool bEnableSetting)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRTShadows(bEnableSetting);
}

void UApolloPlayerSettingsLibrary::SetRTAmbientOcclusionSetting(bool bEnableSetting)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRTAOSetting(bEnableSetting);
}

void UApolloPlayerSettingsLibrary::SetRTReflectionsSetting(bool bEnableSetting)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRTReflectionsSetting(bEnableSetting);
}

void UApolloPlayerSettingsLibrary::SetRTTranslucencySetting(bool bEnableSetting)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRTTranslucencySetting(bEnableSetting);
}

void UApolloPlayerSettingsLibrary::SetPlayerGamepadType(EGamepadType NewGamepadType)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadTypeSetting(NewGamepadType);
}

void UApolloPlayerSettingsLibrary::SetCrouchToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetCrouchToggleSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetSprintToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetSprintToggleSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetRunToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetRunToggleSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetWalkToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetWalkToggleSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetProneToggleSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetProneToggleSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetMouseInvertXSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetMouseXInvertSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetMouseInvertYSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetMouseYInvertSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetGamepadInvertXSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadXInvertSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetGamepadInvertYSetting(bool NewToggleStatus)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadYInvertSetting(NewToggleStatus);

}

void UApolloPlayerSettingsLibrary::SetMouseXSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetMouseXSensitivity(NewSensitivityRate);

}

void UApolloPlayerSettingsLibrary::SetMouseYSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetMouseYSensitivity(NewSensitivityRate);

}

void UApolloPlayerSettingsLibrary::SetGamepadXSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadXSensitivity(NewSensitivityRate);

}

void UApolloPlayerSettingsLibrary::SetGamepadYSensitivitySetting(float NewSensitivityRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadYSensitivity(NewSensitivityRate);

}

void UApolloPlayerSettingsLibrary::SetMouseSmoothRateSetting(float NewSmoothRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetMouseSmoothing(NewSmoothRate);

}

void UApolloPlayerSettingsLibrary::SetGamepadSmoothRateSetting(float NewSmoothRate)
{
	UApolloPlayerSettings* InputSettings = GetMutableDefault<UApolloPlayerSettings>();
	InputSettings->SetGamepadSmoothing(NewSmoothRate);

}


class UTexture2D* UApolloPlayerSettingsLibrary::GetIconForActionByKey(FKey InputAction, UDataTable* CurrentGamepadIconData, UDataTable* KBMIconData, bool bIsGamepad)
{

	static const FString ContextString = InputAction.GetFName().ToString();
	FInputIconMapping* NewIconMapping = nullptr;
	if (bIsGamepad)
	{

		if (InputAction.IsGamepadKey())
		{
			NewIconMapping = CurrentGamepadIconData->FindRow<FInputIconMapping>(InputAction.GetFName(), ContextString, true);
		}

	}
	else
	{
		if (!InputAction.IsGamepadKey())
		{
			NewIconMapping = KBMIconData->FindRow<FInputIconMapping>(InputAction.GetFName(), ContextString, true);
		}
	}


	if (NewIconMapping)
	{
		return NewIconMapping->InputIcon.LoadSynchronous();
	}
	return nullptr;
}

class UTexture2D* UApolloPlayerSettingsLibrary::GetIconForActionByName(FName InputActionName, UDataTable* CurrentGamepadIconData, UDataTable* KBMIconData, bool bIsGamepad)
{
	const UInputSettings* InputSettings = GetMutableDefault<UInputSettings>();
	TArray<FInputActionKeyMapping> NewInputKeyMappings;
	InputSettings->GetActionMappingByName(InputActionName, NewInputKeyMappings);
	FInputActionKeyMapping FoundKeyMapping;
	static const FString ContextString = FoundKeyMapping.Key.GetFName().ToString();
	FInputIconMapping* NewIconMapping = nullptr;
	if (bIsGamepad)
	{
		FoundKeyMapping = NewInputKeyMappings[0];
		if (FoundKeyMapping.Key.IsGamepadKey())
		{
			NewIconMapping = CurrentGamepadIconData->FindRow<FInputIconMapping>(FoundKeyMapping.Key.GetFName(), ContextString, true);
		}
		else
		{
			FoundKeyMapping = NewInputKeyMappings[1];
			if (FoundKeyMapping.Key.IsGamepadKey())
			{
				NewIconMapping = CurrentGamepadIconData->FindRow<FInputIconMapping>(FoundKeyMapping.Key.GetFName(), ContextString, true);
			}
		}

	}
	else
	{
		FoundKeyMapping = NewInputKeyMappings[0];
		if (!FoundKeyMapping.Key.IsGamepadKey())
		{
			NewIconMapping = KBMIconData->FindRow<FInputIconMapping>(FoundKeyMapping.Key.GetFName(), ContextString, true);
		}
		else
		{
			FoundKeyMapping = NewInputKeyMappings[1];
			if (!FoundKeyMapping.Key.IsGamepadKey())
			{
				NewIconMapping = KBMIconData->FindRow<FInputIconMapping>(FoundKeyMapping.Key.GetFName(), ContextString, true);
			}
		}
	}


	if (NewIconMapping)
	{
		return NewIconMapping->InputIcon.LoadSynchronous();
	}
	return nullptr;
}