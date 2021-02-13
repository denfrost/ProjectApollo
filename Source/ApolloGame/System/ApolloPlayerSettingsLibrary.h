// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ApolloGame/System/ApolloPlayerSettings.h"
#include "ApolloPlayerSettingsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class APOLLOGAME_API UApolloPlayerSettingsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		//Get the status of the player's Gamepad Type setting
		UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static EGamepadType GetPlayerGamepadType();

	//Get the status of the player's Crouch toggle setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetCrouchToggleSetting();

	//Get the status of the player's Sprint toggle setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetSprintToggleSetting();

	//Get the status of the player's Run toggle setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetRunToggleSetting();

	//Get the status of the player's Walk toggle setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetWalkToggleSetting();

	//Get the status of the player's Prone toggle setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetProneToggleSetting();

	//Get the status of the player's Mouse Invert X setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetMouseInvertXSetting();

	//Get the status of the player's Mouse Invert Y setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetMouseInvertYSetting();

	//Get the status of the player's Gamepad Invert X setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetGamepadInvertXSetting();

	//Get the status of the player's Mouse Invert Y setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static bool GetGamepadInvertYSetting();

	//Get the status of the player's Mouse X Sensitivity setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetMouseXSensitivitySetting();

	//Get the status of the player's Mouse Y Sensitivity setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetMouseYSensitivitySetting();

	//Get the status of the player's Gamepad X Sensitivity setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetGamepadXSensitivitySetting();

	//Get the status of the player's Gamepad Y Sensitivity setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetGamepadYSensitivitySetting();

	//Get the status of the player's Mouse Smoothing Rate setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetMouseSmoothRateSetting();

	//Get the status of the player's Gamepad Smoothing Rate setting
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
		static float GetGamepadSmoothRateSetting();


	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void ResetAllSettingsToDefault();

	/*UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void ResetInputSettingsToDefault();*/

	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void ResetGameSettingsToDefault();

	//UFUNCTION(BlueprintCallable, Category = "User Settings")
	//	static void ResetVideoSettingsToDefault();

	//UFUNCTION(BlueprintCallable, Category = "User Settings")
	//	static void ResetAudioSettingsToDefault();

	UFUNCTION(BlueprintCallable, BlueprintCallable, Category = "User Settings")
		static FName GetKeyName(FKey KeyPressed);

	//SETTERS

	//Set the status of the player's Gamepad Type setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void SetPlayerGamepadType(EGamepadType NewGamepadType);

	//Set the status of the player's Crouch toggle setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void SetCrouchToggleSetting(bool NewToggleStatus);

	//Set the status of the player's Sprint toggle setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void SetSprintToggleSetting(bool NewToggleStatus);

	//Set the status of the player's Run toggle setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void SetRunToggleSetting(bool NewToggleStatus);

	//Set the status of the player's Walk toggle setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetWalkToggleSetting(bool NewToggleStatus);

	//Set the status of the player's Prone toggle setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetProneToggleSetting(bool NewToggleStatus);

	//Set the status of the player's Mouse Invert X setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetMouseInvertXSetting(bool NewToggleStatus);

	//Set the status of the player's Mouse Invert Y setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetMouseInvertYSetting(bool NewToggleStatus);

	//Set the status of the player's Gamepad Invert X setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetGamepadInvertXSetting(bool NewToggleStatus);

	//Set the status of the player's Mouse Invert Y setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetGamepadInvertYSetting(bool NewToggleStatus);

	//Set the status of the player's Mouse X Sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetMouseXSensitivitySetting(float NewSensitivityRate);

	//Set the status of the player's Mouse Y Sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetMouseYSensitivitySetting(float NewSensitivityRate);

	//Set the status of the player's Gamepad X Sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetGamepadXSensitivitySetting(float NewSensitivityRate);

	//Set the status of the player's Gamepad Y Sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetGamepadYSensitivitySetting(float NewSensitivityRate);

	//Set the status of the player's Mouse Smoothing Rate setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetMouseSmoothRateSetting(float NewSmoothRate);

	//Set the status of the player's Gamepad Smoothing Rate setting
	UFUNCTION(BlueprintCallable, Category = "User Settings")
		static void  SetGamepadSmoothRateSetting(float NewSmoothRate);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
	static class UTexture2D* GetIconForActionByKey(FKey InputAction, UDataTable* CurrentGamepadIconData, UDataTable* KBMIconData, bool bIsGamepad);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "User Settings")
	static class UTexture2D* GetIconForActionByName(FName InputActionName, UDataTable* CurrentGamepadIconData, UDataTable* KBMIconData, bool bIsGamepad);
};
