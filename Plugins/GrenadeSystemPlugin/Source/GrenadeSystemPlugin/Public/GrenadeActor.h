/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"

#include "GrenadeActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGrenadeDetonated, const TArray<class ACharacter*>&, AffectedCharacters);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrenadeThrown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGrenadeCook);

UCLASS(Abstract, Blueprintable)
class GRENADESYSTEMPLUGIN_API AGrenadeActor : public AActor
{
	GENERATED_BODY()


protected:
	
	/** The static mesh for your grenade that you want to throw. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Grenade Mesh")
	class UStaticMeshComponent* m_GrenadeMesh;

	/** To handle bouncing events and velocity of the grenade. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Projectile Movement Component")
	class UProjectileMovementComponent* m_ProjectileMovementComponent;

	/** The mesh that it shown when prediction of trajectory is enabled. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Instanced Static Mesh Component")
	class UInstancedStaticMeshComponent* m_InstancedStaticMeshComponent;

	/** The decal that spawns under the grenade when it's thrown. (prediction of trajectory) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Decal Component")
	class UDecalComponent* m_DecalComponent;

	/** The distance that you want to be able to throw the grenade. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Throw Velocity", meta=(ClampMin="1000", ClampMax="10000"))
	float m_ThrowVelocity;

	/** The time that it takes for the grenade to detonate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Fuze Time", meta = (ClampMin = "1", ClampMax = "10"))
	float m_FuzeTime;

	/** The radius that the grenade can reach. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Radius", meta = (ClampMin = "1", ClampMax = "10000"))
	float m_Radius;

	/** Get the players that are looking at the grenade that are within the radius? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Looking At")
	bool m_bIsLookingAt;                                    

	/** The rotation of the players camera if you want to check if they're looking at the grenade. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Player Rotation", meta = (ClampMin = "1", ClampMax = "180"))
	float m_Rotation;

	/** Is the grenade cookable? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Is Cookable")
	bool m_bIsCookable;

	/** Do you want to detonate the grenade when it bounces? (For example a molotov) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Auto Detonate On Bounce")
	bool m_bAutoDetonateOnBounce;    

	/** The FX actor that will spawn when the grenade is detonated. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Grenade FX")
	TSubclassOf<class AGrenadeFXActor> m_GrenadeFXClass;

	/** The scale of the FX actor that will spawn. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", DisplayName = "Grenade FX Scale")
	FVector m_GrenadeFXActorScale;

	/** Has the grenade detonated yet? */
	UPROPERTY(ReplicatedUsing = OnRep_Detonated)
	bool m_bHasDetonated;

	/** On grenade detonate */
	UFUNCTION()
	void OnRep_Detonated();

	/** Used to replicated variables. */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

protected:

	/**
	 * Predict the trajectory of the grenade
	 * 
	 * @param class UInstancedStaticMeshComponent * InstancedMesh The mesh that will show the path 
	 * @param class UDecalComponent * Decal The end point of the grenade path
	 */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void PredictTrajectory(class UInstancedStaticMeshComponent* InstancedMesh, class UDecalComponent* Decal);

	bool m_bFollow;

	/** Do you want to predict the trajectory of the grenade? (Be sure to set the m_InstancedStaticMeshComponent and the m_DecalComponent) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Predict Trajectory")
	bool m_bPredictTrajectory;

	/** This is intended to return the predicted trajectory, in order to spawn alternative effects if necessary - E Valencia*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Feedback")
	FTransform TrajectoryTransform;
	
private:
	/** Array of the affected characters from this grenade actor. */
	UPROPERTY()
	TArray<class ACharacter*> m_AffectedCharacters;

	/** The timer that detonates the grenade. */
	UPROPERTY()
	FTimerHandle m_GrenadeTimerHandle;

	UPROPERTY()
	class AGrenadeFXActor* m_GrenadeFXActor;

	struct FHitResult m_SurfaceHit;

	bool m_bHasThrown;

	/** Detonating the grenade. */
	void DetonateGrenade();

	/** A quick cleanup of the predict trajectory meshes */
	void CleanupPrediction();

	/**
	 * Get all of the characters in the radius of the grenade actor
	 *
	 * @param TArray<class ACharacter*>& OutCharacters Array of characters that are in the radius
	 * @param bool bIsLookingAt Get only the characters that are looking at the grenade actor?
	 */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void FetchAllCharacters(TArray<class ACharacter*>& OutCharacters, bool bIsLookingAt = false);

public:

	/** Get the grenade static mesh. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE UStaticMeshComponent* GetGrenadeMesh() const { return m_GrenadeMesh; }

	/** Get the projectile movement component. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() { return m_ProjectileMovementComponent; }

	/** Get the throw velocity. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE float GetThrowVelocity() const { return m_ThrowVelocity; }

	/** Get the grenade fuze time. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE float GetFuzeTime() const { return m_FuzeTime; }

	/** Get the characters that are affected by this grenade. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE TArray<class ACharacter*> GetAffectedCharacters() const { return m_AffectedCharacters; }

	/** Get if the grenade is cookable. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE bool IsCookable() const { return m_bIsCookable; }

	/** Get the FX actor that was spawned. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE class AGrenadeFXActor* GetGrenadeFXActor() const { return m_GrenadeFXActor; }

	/** Initialize the grenade timer. */
	void InitGrenade();

	/** Throw the grenade. */
	void ThrowGrenade();

	/** Called when the grenade is detonated. */
	UPROPERTY(BlueprintAssignable)
	FOnGrenadeDetonated OnGrenadeDetonated;

	/** Called when the grenade is thrown. */
	UPROPERTY(BlueprintAssignable)
	FOnGrenadeThrown OnGrenadeThrown;

	/** Called when the grenade is cooked. */
	UPROPERTY(BlueprintAssignable)
	FOnGrenadeCook OnGrenadeCook;

	/** Called when the grenade bounces. */
	UFUNCTION()
	void OnProjectileBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	/** Called when the grenade stops movement. */
	UFUNCTION()
	void OnProjectileStop(const FHitResult& ImpactResult);

	///** Called when the character overlaps with the m_SphereComponent */
	//UFUNCTION()
	//void OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	///** Called when the character stops overlapping with the m_SphereComponent */
	//UFUNCTION()
	//void OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// TODO: Convert to delegate eventually?
	/** Apply damage to characters. - a simple method to add in damage. */
	UFUNCTION()
	virtual void ApplyDamageToCharacters();

public:	
	AGrenadeActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
