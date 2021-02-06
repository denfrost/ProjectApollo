// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CheekyFPS/CheekyFPS.h"
#include "Engine/DeveloperSettings.h"
#include "ApolloPlayerSettings.generated.h"

/**
 * 
 */
UCLASS(config = "PlayerSettings", defaultconfig, meta = (DisplayName = "Player Settings"))
class CHEEKYFPS_API UApolloPlayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	//This will reinitalize user settings to the default values
	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void ResetToDefaultSettings();


	/*Should the player hold down the Crouch key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bCrouchToggle = false;

	/*Should the player hold down the Sprint key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bSprintToggle = false;

	/*Should the player hold down the Run key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bRunToggle = false;

	/*Should the player hold down the Walk key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bWalkToggle = false;

	/*Should the player hold down the Prone key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bProneToggle = true;

	//What gamepad is the player currently using?
	//This will show the correct UI icons for the player's gamepad of choice
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		EGamepadType CurrentGamepadType = EGamepadType::Xbox;

	//Invert the horizontal movement of the mouse
	UPROPERTY(Config, EditAnywhere, Category = "Mouse Settings")
		bool bInvertMouseX = false;

	//Invert the vertical movement of the mouse
	UPROPERTY(Config, EditAnywhere, Category = "Mouse Settings")
		bool bInvertMouseY = false;

	//Invert the horizontal movement of the gamepad
	UPROPERTY(Config, EditAnywhere, Category = "Gamepad Settings")
		bool bInvertGamepadLookX = false;

	//Invert the vertical movement of the mouse
	UPROPERTY(Config, EditAnywhere, Category = "Gamepad Settings")
		bool bInvertGamepadLookY = false;

	//How sensitive should the input react to the mouse's horizontal movement
	UPROPERTY(Config, EditAnywhere, Category = "Mouse Settings")
		float MouseSensitivityX = 1.0f;

	//How sensitive should the input react to the mouse's vertical movement
	UPROPERTY(Config, EditAnywhere, Category = "Mouse Settings")
		float MouseSensitivityY = 1.0f;

	//How sensitive should the input react to the gamepad's horizontal movement
	UPROPERTY(Config, EditAnywhere, Category = "Gamepad Settings")
		float GamepadSensitivityX = 1.0f;

	//How sensitive should the input react to the gamepad's vertical movement
	UPROPERTY(Config, EditAnywhere, Category = "Gamepad Settings")
		float GamepadSensitivityY = 1.0f;


	UPROPERTY(Config, EditAnywhere, Category = "Mouse Settings")
		float MouseLookSmoothingRate = 0.60f;

	UPROPERTY(Config, EditAnywhere, Category = "Gamepad Settings")
		float GamepadLookSmoothingRate = 0.65f;
	
};
