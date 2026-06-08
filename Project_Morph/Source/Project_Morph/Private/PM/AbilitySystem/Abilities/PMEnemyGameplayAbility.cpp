// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/Abilities/PMEnemyGameplayAbility.h"

#include "PM/Character/PMEnemyCharacter.h"

APMEnemyCharacter* UPMEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedPMEnemyCharacter.IsValid())
	{
		CachedPMEnemyCharacter = Cast<APMEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedPMEnemyCharacter.IsValid() ? CachedPMEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UPMEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
