// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "ApolloAIBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class APOLLOGAME_API UApolloAIBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Perception")
	static UAISenseConfig* GetPerceptionSenseConfig(AAIController* Controller, TSubclassOf<UAISense> SenseClass);

	UFUNCTION(BlueprintCallable, Category = "AI|Perception")
		static bool SetSightRange(AAIController* Controller, float SightRange);

	UFUNCTION(BlueprintCallable, Category = "AI|Perception")
		static bool SetHearingRange(AAIController* Controller, float HearingRange);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Perception")
		static float GetSightRange(AAIController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Perception")
		static float GetLoseSightRadius(AAIController* Controller);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Perception")
		static float GetHearingRange(AAIController* Controller);
	
};
