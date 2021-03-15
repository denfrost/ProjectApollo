// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "Engine/GameInstance.h"
#include "ApolloGame/ApolloGame.h"
#include "Engine/DataTable.h"
#include "ApolloGameInstance.generated.h"

class AApolloCharacter;

/*Structure that defines a weapon look up table for the console*/
USTRUCT(BlueprintType)
struct FWeaponSpawnData : public FTableRowBase
{
	GENERATED_BODY()
public:

	FWeaponSpawnData()
		: WeaponName(""),
		WeaponClass(nullptr)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		FString WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TSoftClassPtr<AActor> WeaponClass;
};

/**
 *
 */
UCLASS()
class APOLLOGAME_API UApolloGameInstance : public UGameInstance
{
	GENERATED_BODY()

		UApolloGameInstance();
	void Init() override;
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Console")
	UDataTable* WeaponLookupTable;


	bool bHasPlayerSettingsLoaded;
	float testMouseSensX;
	FString PlayerSettingsIni;


	//Get the name of the current Save Slot
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		FString GetCurrentSaveSlot();	
	
	//Get the name of the current auto Save Slot
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		FString GetCurrentAutoSaveSlot();


	//Get the name of the current Save Slot FilePath
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		FString GetCurrentSaveSlotFilePath();

	//Get the name of the current auto Save Slot File Path
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		FString GetCurrentAutoSaveSlotFilePath();

	//Get the name of the current Save Slots
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetCurrentManualSaveSlots();

	//Get the name of the current auto Save Slots with file path
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetCurrentAutoSaveSlots();

	//Get the name of the possible Save Slots
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetPossibleManualSaveSlots();

	//Get the name of the possible auto Save Slots
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetPossibleAutoSaveSlots();

	//Get the name of the possible Save Slots
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetAllPossibleSaves();

	//Get the name of the Save Slots on disk
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
		TArray<FString> GetAllSavesOnDisk();

	////Get the name of the current auto Save Slot
	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Save System")
	//	FString GetCurrentAutoSaveSlot();


	//Set the name of the current Save Slot
	UFUNCTION(BlueprintCallable, Category = "Save System")
	void SetCurrentSaveSlot(FString NewSaveSlotName);
	

	//Set the name of the current Save Slot with the file path
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetCurrentSaveSlotFilePath(FString NewSaveSlotName);

	//Set the names of the save slots on disk
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetCurrentManualSaves(TArray<FString> NewValidSaveNames);

	//Set the names of the save slots on disk
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetCurrentAutoSaves(TArray<FString> NewValidSaveNames);

	//Set the names of the possible save slots
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetPossibleSaves(TArray<FString> NewValidSaveNames);

	//Set the names of all save slots on disk
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetAllCurrentSaves(TArray<FString> NewValidSaveNames);

	//Set the name of the current auto Save Slot with the file path
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetCurrentAutoSaveSlotFilePath(FString NewSaveSlotName);

	//Set the name of the current auto Save Slot
	UFUNCTION(BlueprintCallable, Category = "Save System")
		void SetCurrentAutoSaveSlot(FString NewSaveSlotName);

	//Set the name of the current auto Save Slot
	UFUNCTION(BlueprintCallable, Category = "Game|Difficulty")
		void SetGameDifficulty(EGameDifficultySetting NewGameDifficulty);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Game|Difficulty")
	EGameDifficultySetting GetGameDifficulty();

	TSoftClassPtr<AActor> WeaponToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console")
	TMap<FString,TSoftClassPtr<AActor>> Weapons;

	UFUNCTION(Exec)
		void SpawnWeapon(FString WeaponName);

	UFUNCTION(Exec)
		void HealPlayer(float HealAmount);

	UFUNCTION(Exec)
		void RecoverMagic(float RecoverAmount);
protected:

	AApolloCharacter* Player;
	
	void InitializeManualSaveArray();
	void InitWeaponArray();

	void InitializeAutoSaveArray();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Game|Difficulty")
	EGameDifficultySetting CurrentGameDifficulty;

	//String of the current Save Slot with the file path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
	FString CurrentSaveSlotFilePath;
	
	//String of the current Save Slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
	FString CurrentSaveSlot;

	//String of the current auto save slot
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		FString CurrentAutoSaveSlot;

	//String of the current auto save slot with the file path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		FString CurrentAutoSaveSlotFilePath;

	//The names of all save slots the player has on disk with file path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> CurrentManualSaveSlotsList;

	//The names of all save slots the player can make
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> ManualSaveSlotsList;

	//The names of all checkpoint save slots the player can make
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> AutoSaveSlotsList;

	//The names of all checkpoint save slots the player has on disk with file path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> CurrentAutoSaveSlotsList;

	//The names of all save slots the player can make
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> AllSaveSlotsList;

	//The names of all checkpoint save slots the player has on disk with file path
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Save System|Slot")
		TArray<FString> AllCurrentSaveSlotsList;

};
