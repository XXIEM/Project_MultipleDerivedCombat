// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"


class APMEnemyCharacter;
class UPMHeroGameplayAbility;
class APMHeroWeapon;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	APMHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	APMHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	void InitHeroWeaponActionMap(APMHeroWeapon* InWeapon);

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	FGameplayTag GetStartActionFromMap(FGameplayTag InputTag, bool& bIsHighPriority, bool& bSuccess) const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	FGameplayTag GetDerivedActionFromMap(FName CurActionID, FGameplayTag InputTag, bool& bSuccess) const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	FGameplayTag GetSpecialActionFromMap(FName CurActionID, FGameplayTag InputTag, bool& bSuccess) const;

	
	//Debug
	void DebugStartActionMap();
	void DebugDerivedActionMap();
	void DebugSpecialActionMap();

	
private:

	//起始招式Map
	TMap<FGameplayTag,TPair<bool,FGameplayTag>> StartActionMap;

	//派生招式Map
	TMap<FName,TMap<FGameplayTag,FGameplayTag>> DerivedActionMap;

	//特殊招式Map
	TMap<FName,TMap<FGameplayTag,TPair<FGameplayTag,FGameplayTag>>> SpecialActionMap;
	
	
};
