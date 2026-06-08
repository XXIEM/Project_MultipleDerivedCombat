// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "PMGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EPMAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};


class UPawnCombatComponent;
class UPMAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	
	//~ Begin UPMGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UPMGameplayAbility Interface

	
	UPROPERTY(EditDefaultsOnly, Category = "PMAbility")
	EPMAbilityActivationPolicy AbilityActivationPolicy = EPMAbilityActivationPolicy::OnTriggered;

	//获取AvatarActor上的CombatComponent
	UFUNCTION(BlueprintPure, Category = "PM|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	//获取AbilitySystemComponent
	UFUNCTION(BlueprintPure, Category = "PM|Ability")
	UPMAbilitySystemComponent* GetPMAbilitySystemComponentFromActorInfo() const;
};
