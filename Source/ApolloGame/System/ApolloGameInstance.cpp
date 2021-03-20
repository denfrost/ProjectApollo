// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ApolloGameInstance.h"
#include "ApolloGame/Character/ApolloCharacter.h"

UApolloGameInstance::UApolloGameInstance()
{
	//On construction initialize save name arrays and find player settings
	bHasPlayerSettingsLoaded = FConfigCacheIni::LoadGlobalIniFile(PlayerSettingsIni, TEXT("PlayerSettings"), NULL, false, false, true, *(FPaths::GeneratedConfigDir()));
	InitializeManualSaveArray();
	InitializeAutoSaveArray();
}

void UApolloGameInstance::Init()
{
	//Set save slot in case it is null and load config settings
	Super::Init();
	if (GetCurrentSaveSlot() == "")
	{
		SetCurrentSaveSlot("SaveSlotA");
	}
	LoadConfig();
	Player = Cast<AApolloCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

}

FString UApolloGameInstance::GetCurrentSaveSlot()
{
	return CurrentSaveSlot;
}

FString UApolloGameInstance::GetCurrentAutoSaveSlot()
{
	return CurrentAutoSaveSlot;
}

FString UApolloGameInstance::GetCurrentSaveSlotFilePath()
{
	return CurrentSaveSlotFilePath;
}

FString UApolloGameInstance::GetCurrentAutoSaveSlotFilePath()
{
	return CurrentAutoSaveSlotFilePath;
}

TArray<FString> UApolloGameInstance::GetCurrentManualSaveSlots()
{
	return CurrentManualSaveSlotsList;
}

TArray<FString> UApolloGameInstance::GetCurrentAutoSaveSlots()
{
	return CurrentAutoSaveSlotsList;
}

TArray<FString> UApolloGameInstance::GetPossibleManualSaveSlots()
{
	return ManualSaveSlotsList;
}

TArray<FString> UApolloGameInstance::GetPossibleAutoSaveSlots()
{
	return AutoSaveSlotsList;
}

TArray<FString> UApolloGameInstance::GetAllPossibleSaves()
{
	return AllSaveSlotsList;
}

TArray<FString> UApolloGameInstance::GetAllSavesOnDisk()
{
	return AllCurrentSaveSlotsList;
}

void UApolloGameInstance::SetCurrentSaveSlot(FString NewSaveSlotName)
{
	CurrentSaveSlot = NewSaveSlotName;
}

void UApolloGameInstance::SetCurrentSaveSlotFilePath(FString NewSaveSlotName)
{
	CurrentSaveSlotFilePath = NewSaveSlotName;
}

void UApolloGameInstance::SetCurrentManualSaves(TArray<FString> NewValidSaveNames)
{
	CurrentManualSaveSlotsList = NewValidSaveNames;
}

void UApolloGameInstance::SetCurrentAutoSaves(TArray<FString> NewValidSaveNames)
{
	CurrentAutoSaveSlotsList = NewValidSaveNames;
}

void UApolloGameInstance::SetPossibleSaves(TArray<FString> NewValidSaveNames)
{
	AllSaveSlotsList = NewValidSaveNames;
}

void UApolloGameInstance::SetAllCurrentSaves(TArray<FString> NewValidSaveNames)
{
	AllCurrentSaveSlotsList = NewValidSaveNames;
}

void UApolloGameInstance::SetCurrentAutoSaveSlotFilePath(FString NewSaveSlotName)
{
	CurrentAutoSaveSlotFilePath = NewSaveSlotName;
}

void UApolloGameInstance::SetCurrentAutoSaveSlot(FString NewSaveSlotName)
{
	CurrentAutoSaveSlot = NewSaveSlotName;
}

void UApolloGameInstance::SetGameDifficulty(EGameDifficultySetting NewGameDifficulty)
{
	CurrentGameDifficulty = NewGameDifficulty;
}

EGameDifficultySetting UApolloGameInstance::GetGameDifficulty()
{
	return CurrentGameDifficulty;
}


void UApolloGameInstance::SpawnWeapon(FString WeaponName)
{
	Player = Cast<AApolloCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	TSubclassOf<AActor> NewWeapon;
	if (Player)
	{
		if (Weapons.Find(WeaponName))
		{
			NewWeapon = Weapons.Find(WeaponName)->Get();
		}

		if (Player->GetClass()->ImplementsInterface(UConsoleCommandInterface::StaticClass()))
		{
			IConsoleCommandInterface::Execute_SpawnNewWeapon(Player, NewWeapon);
		}
	}
	

}

void UApolloGameInstance::HealPlayer(float HealAmount)
{
	if (Player->GetClass()->ImplementsInterface(UConsoleCommandInterface::StaticClass()))
	{
		IConsoleCommandInterface::Execute_HealPlayer(Player, HealAmount);
	}
}

void UApolloGameInstance::RecoverMagic(float RecoverAmount)
{
	if (Player->GetClass()->ImplementsInterface(UConsoleCommandInterface::StaticClass()))
	{
		IConsoleCommandInterface::Execute_RecoverApollo(Player, RecoverAmount);
	}
}

void UApolloGameInstance::InitializeManualSaveArray()
{
	ManualSaveSlotsList.Add("SaveSlotA");
	ManualSaveSlotsList.Add("SaveSlotB");
	ManualSaveSlotsList.Add("SaveSlotC");
	ManualSaveSlotsList.Add("SaveSlotD");
	ManualSaveSlotsList.Add("SaveSlotE");
	ManualSaveSlotsList.Add("SaveSlotF");
	ManualSaveSlotsList.Add("SaveSlotG");


}

void UApolloGameInstance::InitWeaponArray()
{
	//Attempt to add Weapon references through iterating the datatable containing them
	//TArray<FName> RowNames;
	//FString ContextString;
	//RowNames = WeaponLookupTable->GetRowNames();
	//for (auto& name : RowNames)
	//{
	//	FWeaponSpawnData* row = WeaponLookupTable->FindRow<FWeaponSpawnData>(name, ContextString);
	//	if (row)
	//	{
	//		Weapons.Add(row->WeaponClass);
	//	}
	//}
}

void UApolloGameInstance::InitializeAutoSaveArray()
{
	AutoSaveSlotsList.Add("AutoSaveA");
	AutoSaveSlotsList.Add("AutoSaveB");
	AutoSaveSlotsList.Add("AutoSaveC");
	AutoSaveSlotsList.Add("AutoSaveD");
}
