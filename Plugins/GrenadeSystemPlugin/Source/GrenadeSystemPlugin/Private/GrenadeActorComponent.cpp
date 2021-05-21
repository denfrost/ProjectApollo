/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */

#include "GrenadeActorComponent.h"
#include "GrenadeSystem.h"
#include "GrenadePlayerInterface.h"
#include "GrenadeActor.h"

#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"


UGrenadeActorComponent::UGrenadeActorComponent()
{
	m_bAutoAttach = true;
	m_AttachSocketName = "GrenadeSocket";

#if ENGINE_MINOR_VERSION == 23
	bReplicates = true;
#elif ENGINE_MINOR_VERSION == 24
	SetIsReplicated(true);
#elif ENGINE_MINOR_VERSION >= 25
	SetIsReplicatedByDefault(true);
#endif
}

void UGrenadeActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check if the character class of the Owner implements our interface so we can access some helper methods
	if (!GetOwner()->GetClass()->ImplementsInterface(UGrenadePlayerInterface::StaticClass()))
	{
		S9D_PRINT("The character doesn't implement the GrenadePlayerInterface!");
		return;
	}

	// Get and store the characters movement speed so we can use it on grenades such as stun
	ACharacter* const Character = Cast<ACharacter>(GetOwner());
	if (Character)
	{
		m_DefaultWalkSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
	}
}

void UGrenadeActorComponent::SpawnGrenade(uint8 GrenadeToSpawn)
{
	// Check if our array has more than 0 entries before continuing
	if (m_ActorsToSpawn.Num() <= 0)
	{
		S9D_PRINT("Set the Actors To Spawn array in your GrenadeActorComponent!");
		return;
	}

	// Get the specified class of the grenade that we're wanting to spawn via index
	TSubclassOf<class AGrenadeActor> grenadeActor;
	if (m_ActorsToSpawn.IsValidIndex(GrenadeToSpawn))
	{
		grenadeActor = m_ActorsToSpawn[GrenadeToSpawn];
	}

	// If the grenade actor class is valid then continue with execution
	if (grenadeActor == nullptr)
	{
		S9D_PRINT("Selected grenade doesn't exist!");
		return;
	}

	// Spawn the actor of the grenade
	m_GrenadeActor = GetWorld()->SpawnActor<AGrenadeActor>(grenadeActor, FVector::ZeroVector, FRotator::ZeroRotator);
	m_GrenadeActor->SetOwner(GetOwner());

	// Check if the grenade actor should be auto attached to the characters m_AttachSocketName
	if (m_bAutoAttach)
	{
		// Attach the grenade mesh to the characters mesh
		m_GrenadeActor->GetGrenadeMesh()->AttachToComponent((USceneComponent*)IGrenadePlayerInterface::Execute_GetPlayerMesh(GetOwner()), FAttachmentTransformRules::SnapToTargetIncludingScale, m_AttachSocketName);
	}

	// Initialize the grenade actor (ie activate the timer)
	m_GrenadeActor->InitGrenade();
}

void UGrenadeActorComponent::ThrowGrenade(const FRotator SpawnRotation)
{
	// If the grenade actor hasn't spawned then we don't want to continue
	if (m_GrenadeActor == nullptr)
	{
		S9D_PRINT("The grenade actor doesn't exist");
		return;
	}

	// Throw the grenade actor
	m_GrenadeActor->ThrowGrenade();

	// If the grenade actor was automatically attached then lets detach it from our character
	if (m_bAutoAttach)
	{
		m_GrenadeActor->GetGrenadeMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}

	// Cast the owner to a character
	ACharacter* const Character = Cast<ACharacter>(GetOwner());
	if (Character)
	{
		// Cast the character and get the controller of the character
		AController* const Controller = Cast<AController>(Character->GetController());
		if (Controller)
		{
			// Setup the rotation of the grenade from which then we'll get the forward vector of it
			FRotator GrenadeRotation = SpawnRotation == FRotator::ZeroRotator ?
				Controller->GetControlRotation() :
				SpawnRotation;

			// "Throw" the grenade in a specified direction
			m_GrenadeActor->GetProjectileMovementComponent()->Activate();
			m_GrenadeActor->GetProjectileMovementComponent()->Velocity = GrenadeRotation.Vector() * m_GrenadeActor->GetThrowVelocity();
			// m_GrenadeActor->SetOwner(GetOwner());// m_Velocity = GrenadeRotation.Vector() * m_GrenadeActor->GetThrowVelocity();
		}
	}
}
