// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include <Engine/DataTable.h>
#include <Delegates/DelegateCombinations.h>
#include "ISSPlayerController.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamepadDataUpdate);
UCLASS()
class APOLLOGAME_API AISSPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

		AISSPlayerController();

public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Interface")
	class UTexture2D* GetIconForActionByName(FName InputActionName, bool bIsGamepad);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Interface")
		class UTexture2D* GetIconForActionByKey(FKey InputAction, bool bIsGamepad);

	UPROPERTY(BlueprintAssignable, BlueprintCallable,Category = Interface)
		FOnGamepadDataUpdate GamepadDataUpdateDelegate;

	// Implement The Generic Team Interface 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
		FGenericTeamId TeamId;


	UFUNCTION(BlueprintCallable,Category = Interface)
		void UpdateGamepadIconSet(EGamepadType NewGamepadType);

	FGenericTeamId GetGenericTeamId() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
		class UTexture2D* GetInputActionIcon(FName ActionName, bool bIsGamepad);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Input")
		FKey GetInputKeyStruct(FName InputName, bool bIsGamepad);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Input)
		class UTexture2D* GetKeyImage(FKey Key);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Input)
		EGamepadType GetCurrentGamepadType();

	//Holds the key icons for DS3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* DS3IconData;

	//Holds the key icons for DS4
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* DS4IconData;
	
	//Holds the key icons for DualSense
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* DualSenseIconData;

	//Holds the key icons for Xbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* XboxIconData;

	//Holds the key icons for Switch Pro
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* SwitchIconData;

	//Holds the key icons for Steam
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* SteamIconData;

	//Holds the key icons for the Current gamepad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* CurrentGamepadIconData;

	/*
	Holds the key icons for mouse and keyboard
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* KBMIconData;

	//Holds the key icons for DS3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* DS3NameData;

	//Holds the key names for DS4
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* DS4NameData;

	//Holds the key names for DualSense
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* DualSenseNameData;

	//Holds the key names for Xbox
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* XboxNameData;

	//Holds the key names for Switch Pro
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* SwitchNameData;

	//Holds the key names for Steam
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* SteamNameData;
	
	//Holds the key names for KBM
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		UDataTable* KeyboardMouseKeyNameData;

	//Holds the key names for the Current gamepad
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
		UDataTable* CurrentGamepadNameData;

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	EGamepadType CurrentGamepadType;
};
