// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "ISSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHEEKYFPS_API AISSPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

		AISSPlayerController();

public:
	// Implement The Generic Team Interface 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
		FGenericTeamId TeamId;

	FGenericTeamId GetGenericTeamId() const;
};
