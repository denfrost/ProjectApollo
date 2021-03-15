// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ConsoleCommandInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UConsoleCommandInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class APOLLOGAME_API IConsoleCommandInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
		void SpawnNewWeapon(TSubclassOf<AActor> NewWeapon);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
		void HealPlayer(float RecoverAmount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Player")
		void RecoverApollo(float RecoverAmount);

	
};
