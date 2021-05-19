// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ApolloGame/Interfaces/ConsoleCommandInterface.h"
#include "ApolloCharacter.generated.h"

UCLASS()
class APOLLOGAME_API AApolloCharacter : public ACharacter, public IConsoleCommandInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AApolloCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Feedback")
	TArray<TSoftObjectPtr<USoundBase>> DamageSounds;

	UFUNCTION(BlueprintPure, Category = "Feedback")
	USoundBase* GetSound(USoundBase* InSound);

	UFUNCTION(BlueprintPure, Category = "Feedback")
	TSoftObjectPtr<USoundBase> GetLazyLoadedSound(TSoftObjectPtr<USoundBase> InSound);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
