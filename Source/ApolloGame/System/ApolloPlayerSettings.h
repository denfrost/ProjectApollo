// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ApolloGame/ApolloGame.h"
#include "Engine/DeveloperSettings.h"
#include "ApolloPlayerSettings.generated.h"

/**
 * 
 */
UCLASS(config = "PlayerSettings", defaultconfig, meta = (DisplayName = "Player Settings"))
class APOLLOGAME_API UApolloPlayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()


public:

	//This will reinitialize all user settings to the default values
	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void ResetToDefaultSettings();

	//This will reinitialize all mouse settings (sensitivity, smoothing, etc) to default values
	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void ResetMouseSettings();

	//This will reinitialize all gamepad settings (sensitivity, smoothing, etc) to default values
	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void ResetGamepadSettings();

	//This will reinitialize all toggle settings (crouch, sprint, etc) to default values
	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void ResetToggleSettings();

	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void SetCrouchToggleSetting(bool bShouldToggle);

	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void SetSprintToggleSetting(bool bShouldToggle);

	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void SetRunToggleSetting(bool bShouldToggle);

	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void SetWalkToggleSetting(bool bShouldToggle);

	UFUNCTION(BlueprintCallable, Category = "General Settings")
		void SetProneToggleSetting(bool bShouldToggle);

	//This will update the Mouse X sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetMouseXSensitivity(float NewSensitivityRate);

	//This will update the Mouse Y sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetMouseYSensitivity(float NewSensitivityRate);

	//This will update the Mouse Smoothing setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetMouseSmoothing(float NewSmoothingRate);

	//This will update the Mouse X invert setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetMouseXInvertSetting(bool bShouldInvert);

	//This will update the Mouse Y invert setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetMouseYInvertSetting(bool bShouldInvert);

	//This will update the Gamepad X sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "Gamepad Settings")
		void SetGamepadXSensitivity(float NewSensitivityRate);

	//This will update the Gamepad Y sensitivity setting
	UFUNCTION(BlueprintCallable, Category = "Gamepad Settings")
		void SetGamepadYSensitivity(float NewSensitivityRate);

	//This will update the Gamepad X invert setting
	UFUNCTION(BlueprintCallable, Category = "Gamepad Settings")
		void SetGamepadXInvertSetting(bool bShouldInvert);

	//This will update the Gamepad Y invert setting
	UFUNCTION(BlueprintCallable, Category = "Gamepad Settings")
		void SetGamepadYInvertSetting(bool bShouldInvert);

	//This will update the Gamepad Smoothing setting
	UFUNCTION(BlueprintCallable, Category = "Mouse Settings")
		void SetGamepadSmoothing(float NewSmoothingRate);

	//This will update the Gamepad type Setting
	UFUNCTION(BlueprintCallable, Category = "Gamepad Settings")
		void SetGamepadTypeSetting(EGamepadType NewGamepadType);

	//This will update the Raytraced Global Illumination setting
	UFUNCTION(Category = "Graphics Settings|Raytracing")
		void SetRTGISetting(bool bEnableSetting);

	//This will update the Raytraced Shadows setting
	UFUNCTION(Category = "Graphics Settings|Raytracing")
		void SetRTShadows(bool bEnableSetting);

	//This will update the Raytraced Ambient Occlusion setting
	UFUNCTION(Category = "Graphics Settings|Raytracing")
		void SetRTAOSetting(bool bEnableSetting);

	//This will update the Raytraced Reflections setting
	UFUNCTION(Category = "Graphics Settings|Raytracing")
		void SetRTReflectionsSetting(bool bEnableSetting);

	//This will update the Raytraced Translucency setting
	UFUNCTION(Category = "Graphics Settings|Raytracing")
		void SetRTTranslucencySetting(bool bEnableSetting);

	/*Should the player hold down the Crouch key/button or press it?*/
	UPROPERTY(Config, EditAnywhere, Category = "General Settings")
		bool bCrouchToggle = true;

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
		bool bProneToggle = false;

	/*Enable RT based Global Illumination */
	UPROPERTY(Config, EditAnywhere, Category = "Graphics Settings|Raytracing")
		bool bEnableRTGI = true;

	/*Enable RT based Shadows */
	UPROPERTY(Config, EditAnywhere, Category = "Graphics Settings|Raytracing")
		bool bEnableRTShadows = true;

	/*Enable RT based Ambient Occlusion */
	UPROPERTY(Config, EditAnywhere, Category = "Graphics Settings|Raytracing")
		bool bEnableRTAO = false;

	/*Enable RT based Reflections */
	UPROPERTY(Config, EditAnywhere, Category = "Graphics Settings|Raytracing")
		bool bEnableRTReflections = false;

	/*Enable RT based Translucency */
	UPROPERTY(Config, EditAnywhere, Category = "Graphics Settings|Raytracing")
		bool bEnableRTTranslucency = false;


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
