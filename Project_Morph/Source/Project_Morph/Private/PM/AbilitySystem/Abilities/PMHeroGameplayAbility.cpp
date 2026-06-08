// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/Abilities/PMHeroGameplayAbility.h"

#include "PM/Character/PMHeroCharacter.h"
#include "PM/Controllers/PMHeroController.h"

APMHeroCharacter* UPMHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedPMHeroCharacter.IsValid())
	{
		CachedPMHeroCharacter = Cast<APMHeroCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPMHeroCharacter.IsValid() ? CachedPMHeroCharacter.Get() : nullptr;
}

APMHeroController* UPMHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedPMHeroController.IsValid())
	{
		CachedPMHeroController = Cast<APMHeroController>(CurrentActorInfo->PlayerController);
	}

	return CachedPMHeroController.IsValid() ? CachedPMHeroController.Get() : nullptr;
	
}

UHeroCombatComponent* UPMHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
