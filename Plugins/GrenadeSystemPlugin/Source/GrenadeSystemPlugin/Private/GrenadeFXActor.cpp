/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */

#include "GrenadeFXActor.h"
#include "GrenadeActor.h"
#include "GrenadeSystem.h"
#include "GrenadePlayerInterface.h"
#include "GrenadeActorComponent.h"

#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGrenadeFXActor::AGrenadeFXActor()
{
    m_EffectTime = 6.0f;
    m_bAutoResetCharacters = true;
}

void AGrenadeFXActor::Destroyed()
{
    Super::Destroyed();

    ResetAllCharactersToDefault();
}

void AGrenadeFXActor::SetEffectTime(float NewEffectTime)
{
    m_EffectTime = NewEffectTime;
}

void AGrenadeFXActor::ResetAllCharactersToDefault()
{
    if (!m_bAutoResetCharacters)
    {
        return;
    }

    // Array of characters that are affected by the grenade. 
    TArray<class ACharacter*> AffectedCharacters;
    AGrenadeActor* const GrenadeActor = Cast<AGrenadeActor>(GetOwner());
    if (GrenadeActor)
    {
        // Set the array of affected characters to the array from the AGrenadeActor class
        AffectedCharacters = GrenadeActor->GetAffectedCharacters();
    }

    // Iterate over the affected characters
    for (ACharacter* const Character : AffectedCharacters)
    {
        // Check if the Character implements IGrenadePlayerInterface
        if (Character->GetClass()->ImplementsInterface(UGrenadePlayerInterface::StaticClass()))
        {
            // Reset the characters post process settings to default or blank
            IGrenadePlayerInterface::Execute_GetPlayerCamera(Character)->PostProcessSettings = FPostProcessSettings();

            // Reset walk speed if it's modified
            UGrenadeActorComponent* const GrenadeComponent = Cast<UGrenadeActorComponent>(Character->GetComponentByClass(UGrenadeActorComponent::StaticClass()));
            if (GrenadeComponent)
            {
                Character->GetCharacterMovement()->MaxWalkSpeed = GrenadeComponent->GetDefaultWalkSpeed();
                S9D_PRINT("Reset walk speed");
            }
        }
    }
}
