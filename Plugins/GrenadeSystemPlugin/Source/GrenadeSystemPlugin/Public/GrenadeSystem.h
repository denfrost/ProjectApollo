/**
 * Copyright 2019 - S9D Team <s9dteam@gmail.com> https://s9d.xyz
 */

#pragma once

#define DEBUG_INFO 0

/** This file is just a simple config file, feel free to delete this and remove from the classes. */
/** This file is only included in GrenadeActorComponent.cpp and GrenadeActor.cpp so it's pretty easy to remove. Just make sure you remove the macros in the code also. :) */
#if DEBUG_INFO
#define S9D_LOG(str) UE_LOG(LogTemp, Warning, TEXT("S9D/GrenadeSystem: "str));
#define S9D_PRINT(str) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, "S9D/GrenadeSystem: "str)
#else
#define S9D_LOG(str)
#define S9D_PRINT(str)
#endif // DEBUG_INFO