// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Controllers/PMHeroController.h"

APMHeroController::APMHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId APMHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
