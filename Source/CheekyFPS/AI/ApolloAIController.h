// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ApolloAIController.generated.h"

/**
 * 
 */
UCLASS()
class CHEEKYFPS_API AApolloAIController : public AAIController
{
	GENERATED_BODY()

		AApolloAIController();

public:
	//This function helps determine how we respond to something that we've heard or seen
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	//What is our Team
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
		FGenericTeamId TeamId;
};
