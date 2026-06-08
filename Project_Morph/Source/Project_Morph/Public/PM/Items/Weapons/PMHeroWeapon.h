// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "PM/Items/Weapons/PMWeaponBase.h"
#include "PM/PMTypes/PMStructTypes.h"
#include "PMHeroWeapon.generated.h"

/**
 * 
 */
class UPMAbilitySystemComponent;
UCLASS()
class PROJECT_MORPH_API APMHeroWeapon : public APMWeaponBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="WeaponData")
	FPMHeroWeaponData HeroWeaponData;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GetGrantedActionAbilitySpecHandle(UPMAbilitySystemComponent* ASC, FGameplayTag InActionTag) const;
	
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;


	
};
