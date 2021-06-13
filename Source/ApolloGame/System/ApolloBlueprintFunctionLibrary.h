// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/ActorComponent.h"
#include "ApolloBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class APOLLOGAME_API UApolloBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	//Returns the game's resolution, which is typically at 'native' (a 1920x1080 image on a 1920x1080 screen)
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "System|Resolution")
	static FVector2D GetGameResolution();

	//Returns the current viewport's screen space, this may not be the same as the display resolution
	//Resolution may be higher or lower than the actual display
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "System|Viewport")
	static FVector2D GetGameViewportSize();


	UFUNCTION(BlueprintPure, Category = "Feedback")
	static TSoftObjectPtr<USoundBase> GetLazyLoadedSound(TSoftObjectPtr<USoundBase> InSound);
	
	UFUNCTION(BlueprintPure, Category = "Getters")
	static TSoftObjectPtr<UActorComponent> GetLazyLoadedActorComponent(TSoftObjectPtr<UActorComponent> InComponent);

	//Find the edge that intersects between two points at a 90 degree angle
	UFUNCTION(BlueprintPure, Category = "Vector")
	static FVector GetPerpendicularVector(const FVector& Vector);
	
};
