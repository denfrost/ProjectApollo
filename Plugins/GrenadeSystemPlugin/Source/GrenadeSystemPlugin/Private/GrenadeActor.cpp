/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */
#include "GrenadeActor.h"
#include "GrenadeSystem.h"
#include "GrenadeFXActor.h"
#include "GrenadeActorComponent.h"
#include "GrenadePlayerInterface.h"

#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/CollisionProfile.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "GameFramework/ProjectileMovementComponent.h"


AGrenadeActor::AGrenadeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	m_GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GrenadeMesh"));
	m_GrenadeMesh->bCastDynamicShadow = false;
	m_GrenadeMesh->CastShadow = false;
	m_GrenadeMesh->SetSimulatePhysics(false);
	m_GrenadeMesh->SetIsReplicated(true);
	m_GrenadeMesh->SetupAttachment(RootComponent);

	m_ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	m_ProjectileMovementComponent->bShouldBounce = true;
	m_ProjectileMovementComponent->bAutoActivate = false;

	m_InstancedStaticMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstancedStaticMeshComponent"));
	m_InstancedStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	m_DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));

	/*m_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	m_SphereComponent->SetSphereRadius(500.0f);
	m_SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	m_WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	m_WidgetComponent->SetDrawSize(FVector2D(128.0f, 128.0f));
	m_WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_WidgetComponent->SetHiddenInGame(true);
	m_WidgetComponent->SetDrawAtDesiredSize(true);*/
	
	SetReplicateMovement(true);
	SetReplicates(true);

	m_ThrowVelocity = 2000.0f;
	m_FuzeTime = 3.0f;
	m_Radius = 500.0f;
	m_bIsLookingAt = true;
	m_bPredictTrajectory = true;
	m_Rotation = 45;
	m_GrenadeFXActorScale = FVector(2.0f, 2.0f, 2.0f);
}

void AGrenadeActor::BeginPlay()
{
	Super::BeginPlay();

	m_ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &AGrenadeActor::OnProjectileBounce);
	m_ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &AGrenadeActor::OnProjectileStop);

	//m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGrenadeActor::OnSphereOverlapBegin);
	//m_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGrenadeActor::OnSphereOverlapEnd);

	//m_SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//// Attach the widget to the grenade mesh
	//FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, true);
	//m_WidgetComponent->AttachToComponent(m_GrenadeMesh, AttachRules);
	//m_SphereComponent->AttachToComponent(m_GrenadeMesh, AttachRules);
}

void AGrenadeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bPredictTrajectory && !m_bHasDetonated && !m_bHasThrown)
	{
		PredictTrajectory(m_InstancedStaticMeshComponent, m_DecalComponent);
	}
	else
	{
		if (m_bFollow && m_DecalComponent)
		{
			m_DecalComponent->SetWorldLocation(m_GrenadeMesh->K2_GetComponentLocation());
		}
	}
}

void AGrenadeActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGrenadeActor, m_bHasDetonated);
}

void AGrenadeActor::OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (m_bAutoDetonateOnBounce)
	{
		DetonateGrenade();

		// HACK: This fixes the issue where when the grenade bounces again
		m_bAutoDetonateOnBounce = false;
	}

	m_DecalComponent->SetWorldRotation(ImpactResult.ImpactNormal.ToOrientationRotator());
	// m_SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	m_bFollow = true;
}

void AGrenadeActor::OnProjectileStop(const FHitResult& ImpactResult)
{
	m_SurfaceHit = ImpactResult;

	S9D_PRINT("Grenade stopped!");
	// TODO: Do whatever you want to when the projectile has stopped moving
}

//void AGrenadeActor::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (OtherActor != nullptr && OtherActor != this && !OtherActor->IsA<AGrenadeActor>() && m_bHasThrown)
//	{
//		if (m_WidgetComponent && m_WidgetComponent->GetUserWidgetObject())
//		{
//			//ACharacter* const Character = Cast<ACharacter>(GetOwner());
//			//if (Character && Character->IsLocallyControlled())
//			{
//				S9D_PRINT("Overlapping");
//				m_WidgetComponent->GetUserWidgetObject()->AddToViewport();
//				m_WidgetComponent->SetHiddenInGame(false, true);
//			}
//		}
//	}
//}
//
//void AGrenadeActor::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	if (OtherActor != nullptr && OtherActor != this && !OtherActor->IsA<AGrenadeActor>() && m_bHasThrown)
//	{
//		if (m_WidgetComponent && m_WidgetComponent->GetUserWidgetObject())
//		{
//			//ACharacter* const Character = Cast<ACharacter>(GetOwner());
//			//if (Character && Character->IsLocallyControlled())
//			{
//				S9D_PRINT("Not overlapping");
//				m_WidgetComponent->GetUserWidgetObject()->RemoveFromParent();
//				m_WidgetComponent->SetHiddenInGame(false, true);
//			}
//		}
//	}
//}

void AGrenadeActor::ApplyDamageToCharacters()
{
	// Uncomment this code if you want to apply damage to the characters that are in the radius, else leave commented or remove it
	// You'll have to add your own damage system as this product doesn't have a health system implemented

	// Get the characters in the radius, we've already have an array of them m_AffectedCharacters; but this time we're forcing false on bIsLookingAt
	// so we can get an array of the characters that are only in the radius
	// TArray<ACharacter*> AffectedChars;
	// FetchAllCharacters(AffectedChars, false);

	// for (ACharacter* const Character : AffectedChars)
	// {
		// TODO: Implement your own damage system here or even run your damage code in BP using OnGrenadeDetonated event
	// }
}

void AGrenadeActor::InitGrenade()
{
	if (m_bIsCookable)
	{
		// Called when the grenade is cooking
		OnGrenadeCook.Broadcast();
		
		// If the grenade is cookable then go ahead and start the timer if it's not already active.
		if (!GetWorldTimerManager().IsTimerActive(m_GrenadeTimerHandle))
		{
			GetWorldTimerManager().SetTimer(m_GrenadeTimerHandle, this, &AGrenadeActor::DetonateGrenade, m_FuzeTime, false);
		}
	}
}

void AGrenadeActor::ThrowGrenade()
{
	if (m_bHasDetonated)
	{
		S9D_PRINT("The grenade has already exploded so you can't throw it.");
		return;
	}

	m_bHasThrown = true;

	S9D_PRINT("Thrown");

	// Called when the grenade is thrown
	OnGrenadeThrown.Broadcast();

	// If the grenade isn't cookable then go ahead and start the timer if it's not already active.
	if (!GetWorldTimerManager().IsTimerActive(m_GrenadeTimerHandle))
	{
		GetWorldTimerManager().SetTimer(m_GrenadeTimerHandle, this, &AGrenadeActor::DetonateGrenade, m_FuzeTime, false);
	}

	CleanupPrediction();
}

void AGrenadeActor::OnRep_Detonated()
{
	// Get the characters within a radius of the grenade actor (m_Radius)
	FetchAllCharacters(m_AffectedCharacters, m_bIsLookingAt);

	// Spawn fx actor
	FTransform Trans;
	Trans.SetScale3D(m_GrenadeFXActorScale);
	Trans.SetLocation(GetActorLocation());
	m_GrenadeFXActor = GetWorld()->SpawnActorDeferred<AGrenadeFXActor>(m_GrenadeFXClass, Trans);
	if (m_GrenadeFXActor)
	{
		m_GrenadeFXActor->SetLifeSpan(m_FuzeTime * 3);
		m_GrenadeFXActor->SetEffectTime(m_FuzeTime * 3 - 1); // This may cause issues with setting it in the actor since we're setting it before it's spawned
		m_GrenadeFXActor->SetOwner(this);
		m_GrenadeFXActor->FinishSpawning(Trans);
	}

	// When the grenade is detonated call the Blueprint event and pass along the characters that are within the radius
	OnGrenadeDetonated.Broadcast(m_AffectedCharacters);

	// Apply damage to the characters in the radius of the grenade
	ApplyDamageToCharacters();

	// On detonation of the grenade, hide the static mesh
	m_GrenadeMesh->SetVisibility(false);

	// Disable the mesh collision so if our character walks in the area we don't hit it.
	m_GrenadeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set the life span of the actor to help free up memory
	SetLifeSpan(m_FuzeTime * 3);
}

void AGrenadeActor::DetonateGrenade()
{
	S9D_PRINT("Detonated");

	// Do a quick cleanup on the prediction code
	CleanupPrediction();
	
	//// Destroy the widget component
	//if (m_WidgetComponent)
	//{
	//	m_WidgetComponent->DestroyComponent();
	//}
	//// Destroy the sphere component
	//if (m_SphereComponent)
	//{
	//	m_SphereComponent->DestroyComponent();
	//}

	m_bHasDetonated = true;
	OnRep_Detonated();

	// Destroy the decal
	if (m_DecalComponent)
	{
		m_DecalComponent->DestroyComponent();
	}
}

void AGrenadeActor::CleanupPrediction()
{
	m_bPredictTrajectory = false;

	// Detach prediction meshes
	if (m_InstancedStaticMeshComponent)
	{
		m_InstancedStaticMeshComponent->DestroyComponent();
	}
	if (m_DecalComponent)
	{
		FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepRelative, true);
		m_DecalComponent->DetachFromComponent(DetachRules);
	}
}

void AGrenadeActor::FetchAllCharacters(TArray<class ACharacter*>& OutCharacters, bool bIsLookingAt)
{
	if (GetWorld())
	{
		OutCharacters.Reset();
		for (TActorIterator<ACharacter> Itr(GetWorld()); Itr; ++Itr)
		{
			ACharacter* const Char = Cast<ACharacter>(*Itr);

			// Check if the character is within the radius of the grenade actor
			if (Char->GetDistanceTo(this) <= m_Radius)
			{
				S9D_PRINT("Got character: " + Char->GetName());
				
				// Check if the player is looking at the grenade actor
				if (bIsLookingAt)
				{ 
					bool bIsLookingAtGrenade = false;

					// Setup some local variables
					FRotator PlayerRotation = Char->GetActorRotation();
					FVector PlayerLocation = Char->GetActorLocation();

					FVector GrenadeLocation = GetActorLocation();

					FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, GrenadeLocation);
					FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(PlayerRotation, LookRotation);

					// Checks horizontal rotation
					if (Delta.Yaw >= -m_Rotation && Delta.Yaw <= m_Rotation)
					{
						FVector EndLocation = LookRotation.Vector() * -100.0f + PlayerLocation;

						// Perform a simple line trace to determine if the player (Char) is looking at the grenade actor
						FHitResult HitRes;
						FCollisionQueryParams CollisionParams;
						CollisionParams.AddIgnoredActor(this);

						if (GetWorld()->LineTraceSingleByChannel(HitRes, GrenadeLocation, EndLocation, ECC_Pawn, CollisionParams))
						{
							// Determine if the actor that the line trace hit was a character
							ACharacter* const HitResActor = Cast<ACharacter>(HitRes.Actor);
							if (HitResActor)
							{
								bIsLookingAtGrenade = HitResActor == Char;
							}
						}
					}

					if (!bIsLookingAtGrenade)
					{
						continue;
					}
				}

				// Add the character to our array
				OutCharacters.Add(*Itr);
			}
		}
	}
}

void AGrenadeActor::PredictTrajectory(class UInstancedStaticMeshComponent* InstancedMesh, class UDecalComponent* Decal)
{
	if (InstancedMesh)
	{
		// Clear instance mesh
		InstancedMesh->ClearInstances();
	}

	FHitResult HitRes;
	TArray<FVector> Points;
	FVector LastTraceDestination;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TArray<AActor*> IgnoredActors;

	// Get the velocity from the character (the forward vector and multiply by the m_ThrowVelocity)
	FVector velocity;
	ACharacter* const Character = Cast<ACharacter>(GetOwner());
	if (Character)
	{
		AController* const Controller = Cast<AController>(Character->GetController());
		if (Controller)
		{
			velocity = Controller->GetControlRotation().Vector() * m_ThrowVelocity;
		}
	}

	// Perform the trace to determine where the projectile will land
	UGameplayStatics::Blueprint_PredictProjectilePath_ByObjectType(GetWorld(), HitRes, Points, LastTraceDestination, m_GrenadeMesh->K2_GetComponentLocation(), velocity, true, 12.0f, ObjectTypes, false, IgnoredActors, EDrawDebugTrace::None, 0.0f, 32.0f);

	// Iterate over all points except the first and last
	for (int32 i = 1; i < Points.Num() - 2; i++)
	{
		// Setup the math for determining the trajectory
		FVector point = Points.IsValidIndex(i) ? Points[i] : FVector();
		FVector point1 = Points.IsValidIndex(i + 1) ? Points[i + 1] : FVector();
		FRotator NewRot = (point1 - point).ToOrientationRotator().Add(90.0f, 0.0f, 0.0f);
		FTransform Trans = UKismetMathLibrary::MakeTransform(point, NewRot, FVector(1.0f, 1.0f, 1.0f));
		TrajectoryTransform = Trans;
		if (i + 1 < InstancedMesh->GetInstanceCount())
		{
			InstancedMesh->UpdateInstanceTransform(i, Trans, true, false, true);
		}
		else
		{
			InstancedMesh->AddInstanceWorldSpace(Trans);
		}
	}

	// Spawn a decal where the grenade detonates
	if (Decal)
	{
		if (HitRes.bBlockingHit)
		{
			FTransform Trans = UKismetMathLibrary::MakeTransform(HitRes.ImpactPoint, HitRes.ImpactNormal.ToOrientationRotator(), FVector(1.0f, 1.0f, 1.0f));
			Decal->SetWorldTransform(Trans);
		}
		else
		{
			Decal->SetHiddenInGame(true);
		}
	}
}

