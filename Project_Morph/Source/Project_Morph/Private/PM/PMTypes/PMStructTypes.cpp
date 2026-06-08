// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/PMTypes/PMStructTypes.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"


bool FPMHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

bool FPMHeroActionAbilitySet::IsValid() const
{
	return ActionTag.IsValid() && AbilityToGrant;
}
