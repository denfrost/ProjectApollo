// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "ApolloGame/Character/ApolloCharacter.h"
#include <Sound/SoundBase.h>

// Sets default values
AApolloCharacter::AApolloCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


USoundBase* AApolloCharacter::GetSound(USoundBase* InSound)
{
	return InSound;
}

TSoftObjectPtr<USoundBase> AApolloCharacter::GetLazyLoadedSound(TSoftObjectPtr<USoundBase> InSound)
{
	return InSound.LoadSynchronous();
}

// Called when the game starts or when spawned
void AApolloCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AApolloCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AApolloCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

