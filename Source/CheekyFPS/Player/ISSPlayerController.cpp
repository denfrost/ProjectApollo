// Fill out your copyright notice in the Description page of Project Settings.


#include "ISSPlayerController.h"

AISSPlayerController::AISSPlayerController()
{
	SetGenericTeamId(FGenericTeamId(TeamId));
}

FGenericTeamId AISSPlayerController::GetGenericTeamId() const
{
	return TeamId;
}
