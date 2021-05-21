/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrenadePlayerInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UGrenadePlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRENADESYSTEMPLUGIN_API IGrenadePlayerInterface
{
	GENERATED_BODY()
         
public:
    /** Get the camera of the character to apply effects. */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "S9D|Grenade Component")
    class UCameraComponent* GetPlayerCamera() const;

    /** Get the mesh to attach the grenade actor to. */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "S9D|Grenade Component")
	class USkeletalMeshComponent* GetPlayerMesh() const;
};
