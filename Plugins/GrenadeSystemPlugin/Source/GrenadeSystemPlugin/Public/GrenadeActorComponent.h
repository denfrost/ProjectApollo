/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrenadeActorComponent.generated.h"


UENUM(BlueprintType)
enum class EGrenadeAnim : uint8
{
	GA_None		UMETA(DisplayName = "None"),
	GA_Equip	UMETA(DisplayName = "Equip"),
	GA_Throw	UMETA(DisplayName = "Throw"),
	GA_Cancel	UMETA(DisplayName = "Cancel")
};

UCLASS( ClassGroup=(S9D), meta=(BlueprintSpawnableComponent) )
class GRENADESYSTEMPLUGIN_API UGrenadeActorComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/** An array of grenade actors that you want to be able to spawn with this component. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Actors To Spawn")
	TArray<TSubclassOf<class AGrenadeActor>> m_ActorsToSpawn;

	/** Do you want to auto attach the grenade mesh to a socket? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Attach to Socket")
	bool m_bAutoAttach;

	/** The socket to attach the grenade mesh to. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings", DisplayName = "Socket Name")
	FName m_AttachSocketName;
private:

	/** The grenade actor pointer to be able to access data from it. */
	UPROPERTY()
	class AGrenadeActor* m_GrenadeActor;

	UPROPERTY()
	float m_DefaultWalkSpeed;

public:	

	/**
	 * Spawn a grenade into the world
	 * 
	 * @param uint8 GrenadeToSpawn The index of the grenade that you want to spawn (from the ActorsToSpawn array)
	 */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void SpawnGrenade(uint8 GrenadeToSpawn);

	/**
	 * Throw a grenade to the specified location.
	 *
	 * @param const FRotator & SpawnRotation The rotation that the grenade should spawn to
	 */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void ThrowGrenade(const FRotator SpawnRotation = FRotator::ZeroRotator);

	/** Get the grenade actor that was spawned. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE class AGrenadeActor* GetGrenadeActor() const { return m_GrenadeActor; }

	/** Get the default walk speed of the character. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE float GetDefaultWalkSpeed() const { return m_DefaultWalkSpeed; }

	/** Has the grenade detonated? */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE bool HasDetonated() const { return m_GrenadeActor == nullptr; } // This isn't an ideal way to verify that it's detonated, but m_bHasDetonated won't work for this situation since the actor will be null

public:

	UGrenadeActorComponent();

	virtual void BeginPlay() override;
};
