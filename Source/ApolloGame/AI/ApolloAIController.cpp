// Fill out your copyright notice in the Description page of Project Settings.


#include "ApolloAIController.h"
#include <Perception/AIPerceptionSystem.h>

AApolloAIController::AApolloAIController()
{
	
	//PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	
}

ETeamAttitude::Type AApolloAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			//Other controllers with an ID of 5 are Friendly
			FGenericTeamId OtherTeamID = TeamAgent->GetGenericTeamId();
			if (OtherTeamID == 5)
			{
			UE_LOG(LogTemp, Verbose, TEXT("Detected Friendly Actor"));
				return ETeamAttitude::Friendly;
			}
			//Controllers with an ID of 18 are Hostile - the player
			if (OtherTeamID == 18)
			{
				UE_LOG(LogTemp, Verbose, TEXT("Detected Enemy Actor"));
				return ETeamAttitude::Hostile;
			}
			//Controllers with an ID of 10 are Neutral
			if (OtherTeamID == 10)
			{
				return ETeamAttitude::Neutral;
			}
		}
	}

	return ETeamAttitude::Neutral;
}

void AApolloAIController::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(FGenericTeamId(TeamId));
	//UAIPerceptionSystem::GetCurrent(GetWorld())->UpdateListener(*PerceptionComponent);
}

