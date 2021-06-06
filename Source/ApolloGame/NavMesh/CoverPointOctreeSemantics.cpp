// Copyright Infinity Starlight Studios 2021. All Rights Reserved (unless otherwise specified)


#include "CoverPointOctreeSemantics.h"
#include "ApolloGame/System/ApolloCoverSystemLibrary.h"


void FCoverPointOctreeSemantics::SetElementId(const FCoverPointOctreeElement& Element, FOctreeElementId2 ID)
{
	UWorld* World = nullptr;
	UObject* ElementOwner = Element.GetOwner();
	AActor* Actor = Cast<AActor>(ElementOwner);
	UActorComponent* AC = Cast<UActorComponent>(ElementOwner);
	ULevel* Level = Cast<ULevel>(ElementOwner);
	if(Actor)
	{
		World = Actor->GetWorld();
	}
	else if (AC)
	{
		World = AC->GetWorld();	
	}
	else if (Level)
	{
		World = Level->OwningWorld;
	}

	if(UApolloCoverSystemLibrary::bShutdown)
	{
		return;
	}
	UApolloCoverSystemLibrary::GetInstance(World)->AssignIDToElement(Element.Data->Location, ID);
		
}
