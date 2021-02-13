// Fill out your copyright notice in the Description page of Project Settings.

/*This code is largely based on original programming by v.s. and Modeus Games from https://answers.unrealengine.com/questions/547078/modify-ai-perception-sense-range-during-runtime-1.html */

#include "ApolloAIBlueprintLibrary.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"

UAISenseConfig* UApolloAIBlueprintLibrary::GetPerceptionSenseConfig(AAIController* Controller, TSubclassOf<UAISense> SenseClass)
{
	UAISenseConfig* result = nullptr;

	FAISenseID Id = UAISense::GetSenseID(SenseClass);
	if (!Id.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("GetPerceptionSenseConfig: Wrong Sense ID"));
	}
	else if (Controller == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetPerceptionSenseConfig: Controller == nullptr"));
	}
	else
	{
		UAIPerceptionComponent* Perception = Controller->GetAIPerceptionComponent();
		if (Perception == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("GetPerceptionSenseConfig: Perception == nullptr"));
		}
		else
		{
			result = Perception->GetSenseConfig(Id);
		}
	}

	return result;
}

bool UApolloAIBlueprintLibrary::SetSightRange(AAIController* Controller, float SightRange)
{
	UAISenseConfig* Config = GetPerceptionSenseConfig(Controller, UAISense_Sight::StaticClass());
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SetSightRange: Config == nullptr"));
		return false;
	}
	else
	{
		UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Config);

		UE_LOG(LogTemp, Verbose, TEXT("SetSightRange was %f %f, setting to %f %f")
			, ConfigSight->SightRadius, ConfigSight->LoseSightRadius, SightRange, (ConfigSight->LoseSightRadius - ConfigSight->SightRadius + SightRange));

		// Save original lose range
		float LoseRange = ConfigSight->LoseSightRadius - ConfigSight->SightRadius;
		ConfigSight->SightRadius = SightRange;
		// Apply lose range to new radius of the sight
		ConfigSight->LoseSightRadius = ConfigSight->SightRadius + LoseRange;
		UAIPerceptionComponent* Perception = Controller->GetAIPerceptionComponent();
		Perception->RequestStimuliListenerUpdate();
	}

	return true;
}

bool UApolloAIBlueprintLibrary::SetHearingRange(AAIController* Controller, float HearingRange)
{
	UAISenseConfig* Config = GetPerceptionSenseConfig(Controller, UAISense_Hearing::StaticClass());
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get Hearing Config!"));
		return false;
	}
	else
	{
		UAISenseConfig_Hearing* ConfigHearing = Cast<UAISenseConfig_Hearing>(Config);
		UE_LOG(LogTemp, Verbose, TEXT("SetSightRange was %f, setting to  %f"), ConfigHearing->HearingRange, HearingRange, (HearingRange));
		ConfigHearing->HearingRange = HearingRange;
		UAIPerceptionComponent* Perception = Controller->GetAIPerceptionComponent();
		Perception->RequestStimuliListenerUpdate();
	}
	return true;
}

float UApolloAIBlueprintLibrary::GetSightRange(AAIController* Controller)
{
	UAISenseConfig* Config = GetPerceptionSenseConfig(Controller, UAISense_Sight::StaticClass());
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get Sight Config!"));
		return 0.0f;
	}
	else
	{
		UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(Config);
		UE_LOG(LogTemp, Warning, TEXT("Got Sight Range of %f"), ConfigSight->SightRadius);
		return ConfigSight->SightRadius;

	}
	return 0.0f;
}

float UApolloAIBlueprintLibrary::GetHearingRange(AAIController* Controller)
{
	UAISenseConfig* Config = GetPerceptionSenseConfig(Controller, UAISense_Hearing::StaticClass());
	if (Config == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to get Hearing Config!"));
		return 0.0f;
	}
	else
	{
		UAISenseConfig_Hearing* ConfigHearing = Cast<UAISenseConfig_Hearing>(Config);
		UE_LOG(LogTemp, Warning, TEXT("Got Hearing Range of %f"), ConfigHearing->HearingRange);
		return ConfigHearing->HearingRange;
	}
	return 0.0f;
}
