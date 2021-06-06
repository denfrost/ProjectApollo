// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloBlueprintFunctionLibrary.h"

FVector2D UApolloBlueprintFunctionLibrary::GetGameResolution()
{
	FVector2D Result = FVector2D(1, 1);

	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;

	return Result;
}

FVector2D UApolloBlueprintFunctionLibrary::GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	return Result;
}

TSoftObjectPtr<USoundBase> UApolloBlueprintFunctionLibrary::GetLazyLoadedSound(TSoftObjectPtr<USoundBase> InSound)
{
	if(InSound)
	{
		return InSound.LoadSynchronous();
	}
	return nullptr;
}

TSoftObjectPtr<UActorComponent> UApolloBlueprintFunctionLibrary::GetLazyLoadedActorComponent(
	TSoftObjectPtr<UActorComponent> InComponent)
{
	if(InComponent)
	{
		return InComponent.LoadSynchronous();
	}
	return nullptr;
}

