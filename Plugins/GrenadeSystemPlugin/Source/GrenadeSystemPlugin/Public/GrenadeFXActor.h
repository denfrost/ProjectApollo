/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrenadeFXActor.generated.h"


UCLASS(Abstract, Blueprintable)
class GRENADESYSTEMPLUGIN_API AGrenadeFXActor : public AActor
{
	GENERATED_BODY()

	float m_TmpMovementSpeed;

protected:
	/** How long should the effect play for? (This should be atleast 1 less than your (m_FuzeTime * 3), so 8)*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "S9D|Grenade Component", DisplayName = "Effect Time", meta=(ClampMin="1", ClampMax="60"))
	float m_EffectTime;

	/** Do you want to clear the post process on affected characters on destroy? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "S9D|Grenade Component", DisplayName = "Clear Post Process on Destroy")
	bool m_bAutoResetCharacters;

public:
	/** Get the effect time. */
	UFUNCTION(BlueprintPure, Category = "S9D|Grenade Component")
	FORCEINLINE float GetEffectTime() const { return m_EffectTime; }

	/**
	 * Set a new effect time
	 * 
	 * @param float NewEffectTime The new time that you're setting
	 */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void SetEffectTime(float NewEffectTime);

	/** Reset all affected characters to default settings. */
	UFUNCTION(BlueprintCallable, Category = "S9D|Grenade Component")
	void ResetAllCharactersToDefault();

public:
	AGrenadeFXActor();

	virtual void Destroyed() override;
};
