// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"
#include "PMEnemyGameplayAbility.generated.h"

class APMEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMEnemyGameplayAbility : public UPMGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "PM|Ability")
	APMEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "PM|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<APMEnemyCharacter> CachedPMEnemyCharacter;

	
};
