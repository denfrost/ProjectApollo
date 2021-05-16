// Fill out your copyright notice in the Description page of Project Settings.


#include "ISSPlayerController.h"
#include <GameFramework/PlayerInput.h>
#include <GameFramework/InputSettings.h>
#include "UINavigation/Public/Data/InputIconMapping.h"
#include "ApolloGame/ApolloGame.h"


AISSPlayerController::AISSPlayerController()
{
	TeamId = 18;
	SetGenericTeamId(FGenericTeamId(TeamId));
}

class UTexture2D* AISSPlayerController::GetIconForActionByName(FName InputActionName, bool bIsGamepad)
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

class UTexture2D* AISSPlayerController::GetIconForActionByKey(FKey InputAction, bool bIsGamepad)
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

void AISSPlayerController::UpdateGamepadIconSet(EGamepadType NewGamepadType)
{
	CurrentGamepadType = NewGamepadType;
	switch (CurrentGamepadType)
	{
	case EGamepadType::None:
	{
		break;
	}
	case EGamepadType::Xbox:
	{
		CurrentGamepadIconData = XboxIconData;
		CurrentGamepadNameData = XboxNameData;
		break;
	}
	case EGamepadType::DS3:
	{
		CurrentGamepadIconData = DS3IconData;
		CurrentGamepadNameData = DS3IconData;
		break;
	}
		
	case EGamepadType::DS4:
	{
		CurrentGamepadIconData = DS4IconData;
		CurrentGamepadNameData = DS4NameData;
		break;
	}
	case EGamepadType::DS5:
	{
		CurrentGamepadIconData = DualSenseIconData;
		CurrentGamepadNameData = DualSenseNameData;
		break;
	}
	case EGamepadType::SwitchPro:
	{
		CurrentGamepadIconData = SwitchIconData;
		CurrentGamepadNameData = SwitchNameData;
		break;
	}
	case EGamepadType::Steam:
	{
		CurrentGamepadIconData = SteamIconData;
		CurrentGamepadNameData = SteamNameData;
		break;
	}
	default:
		break;
	}

	GamepadDataUpdateDelegate.Broadcast();
}

FGenericTeamId AISSPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

class UTexture2D* AISSPlayerController::GetInputActionIcon(FName ActionName, bool bIsGamepad)
{
	FKey Key = GetInputKeyStruct(ActionName, bIsGamepad);
	return GetKeyImage(Key);
}

FKey AISSPlayerController::GetInputKeyStruct(FName InputName, bool bIsGamepad)
{
	FString InputString = InputName.ToString();
	FString AxisScale = InputString.Right(1);
	//EAxisType AxisType = EAxisType::None;
	//if (AxisScale.Equals(TEXT("+"))) AxisType = EAxisType::Positive;
	//else if (AxisScale.Equals(TEXT("-"))) AxisType = EAxisType::Negative;

	const UInputSettings* Settings = GetDefault<UInputSettings>();

	TArray<FInputActionKeyMapping> ActionMappings;
	Settings->GetActionMappingByName(InputName, ActionMappings);

	int Iterations = ActionMappings.Num();
	for (int i = Iterations - 1; i >= 0; --i)
	{
		if (bIsGamepad)
		{
			if (ActionMappings[i].Key.IsGamepadKey())
			{
				return ActionMappings[i].Key;
			}
		}
		else
		{
			return ActionMappings[i].Key;
		}

	}
	return FKey();
	/*else
	{
		InputName = FName(*InputString.Left(InputString.Len() - 1));
		TArray<FInputAxisKeyMapping> AxisMappings;
		Settings->GetAxisMappingByName(InputName, AxisMappings);

		FKey PotentialAxisKey;
		int Iterations = AxisMappings.Num();
		for (int i = Iterations - 1; i >= 0; --i)
		{
			if (UUINavBlueprintFunctionLibrary::RespectsRestriction(AxisMappings[i].Key, InputRestriction))
			{
				if ((AxisMappings[i].Scale > 0.0f && AxisType == EAxisType::Positive) ||
					(AxisMappings[i].Scale < 0.0f && AxisType == EAxisType::Negative))
				{
					return AxisMappings[i].Key;
				}
				else
				{
					PotentialAxisKey = GetKeyFromAxis(AxisMappings[i].Key, AxisType == EAxisType::Positive);
					if (PotentialAxisKey.IsValid())
					{
						return PotentialAxisKey;
					}
				}
			}
		}
		return FKey();
	}*/
}

class UTexture2D* AISSPlayerController::GetKeyImage(FKey Key)
{
	FInputIconMapping* KeyIcon = nullptr;

	if (Key.IsGamepadKey())
	{
		if (CurrentGamepadIconData != nullptr && CurrentGamepadIconData->GetRowMap().Contains(Key.GetFName()))
		{
			KeyIcon = (FInputIconMapping*)CurrentGamepadIconData->GetRowMap()[Key.GetFName()];
		}
	}
	else
	{
		if (KBMIconData != nullptr && KBMIconData->GetRowMap().Contains(Key.GetFName()))
		{
			KeyIcon = (FInputIconMapping*)KBMIconData->GetRowMap()[Key.GetFName()];
		}
		
	}

	if (KeyIcon == nullptr)
	{
		return nullptr;
	}

	UTexture2D* NewTexture = KeyIcon->InputIcon.LoadSynchronous();
	return NewTexture;
}

EGamepadType AISSPlayerController::GetCurrentGamepadType()
{
	return CurrentGamepadType;
}
