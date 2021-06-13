// Copyright Epic Games, Inc. All Rights Reserved.


#include "ApolloGameGameModeBase.h"
#include "NavMesh/CoverOctree.h"
#include "NavMesh/CoverPointOctreeElement.h"
#include "System/ChangeNotifyRecastNavMesh.h"
#if DEBUG_RENDERING
#include "DrawDebugHelpers.h"
#endif


AApolloGameGameModeBase::AApolloGameGameModeBase()
{
	
}

void AApolloGameGameModeBase::PostLoad()
{
	Super::PostLoad();
}

void AApolloGameGameModeBase::OnWorldInitDelegate(UWorld* World, const UWorld::InitializationValues IVS)
{
	
}

void AApolloGameGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AApolloGameGameModeBase::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AApolloGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ApolloCoverSystem->bShutdown = false;
	ApolloCoverSystem = UApolloCoverSystemLibrary::GetInstance(GetWorld());
	ApolloCoverSystem->MapBounds = MapBounds;
#if DEBUG_RENDERING
	ApolloCoverSystem->bDebugDraw = bDebugDraw;
#endif
}

void AApolloGameGameModeBase::DebugShowCoverPoints()
{
#if DEBUG_RENDERING
	UWorld* CurrentWorld = GetWorld();
	FlushPersistentDebugLines(CurrentWorld);
	TArray<FCoverPointOctreeElement> CoverPoints;

	if(UApolloCoverSystemLibrary::bShutdown)
	{
		return;
	}
	UApolloCoverSystemLibrary::GetInstance(CurrentWorld)->FindCoverPoints_Box(CoverPoints, FBoxCenterAndExtent(FVector::ZeroVector, FVector(64000.0f)).GetBox());
	for(FCoverPointOctreeElement CP : CoverPoints)
	{
		DrawDebugSphere(CurrentWorld,CP.Data->Location,25,4,CP.Data->bIsTaken ? FColor::Red : CP.Data->bIsForceField ? FColor::Orange : FColor::Blue,true,-1,0,5);
	}
#endif
	
}

void AApolloGameGameModeBase::ForceGC()
{
#if DEBUG_RENDERING
	GEngine->ForceGarbageCollection(true);
#endif
}

void AApolloGameGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
		Super::EndPlay(EndPlayReason);

	ApolloCoverSystem->bShutdown = true;
	ApolloCoverSystem = nullptr;
}

void AApolloGameGameModeBase::PostActorCreated()
{
		Super::PostActorCreated();
}
