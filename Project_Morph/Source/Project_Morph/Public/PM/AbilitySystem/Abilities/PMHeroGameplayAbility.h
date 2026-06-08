// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"
#include "PMHeroGameplayAbility.generated.h"

class UHeroCombatComponent;
class APMHeroController;
class APMHeroCharacter;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMHeroGameplayAbility : public UPMGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="PM|Ability")
	APMHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="PM|Ability")
	APMHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="PM|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	
	
private:
	//保存主角对象的弱指针引用
	TWeakObjectPtr<APMHeroCharacter> CachedPMHeroCharacter;

	//保存主角控制器的弱指针引用
	TWeakObjectPtr<APMHeroController>  CachedPMHeroController;
		
};
