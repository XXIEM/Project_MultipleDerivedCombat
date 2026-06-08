// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/Components/Combat/PawnCombatComponent.h"

void UPMGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if(AbilityActivationPolicy == EPMAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UPMGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AbilityActivationPolicy == EPMAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
	
}

UPawnCombatComponent* UPMGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UPMAbilitySystemComponent* UPMGameplayAbility::GetPMAbilitySystemComponentFromActorInfo() const
{
	return Cast<UPMAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
