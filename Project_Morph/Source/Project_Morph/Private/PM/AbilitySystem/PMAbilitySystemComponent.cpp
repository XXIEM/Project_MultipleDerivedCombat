// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"


void UPMAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid())
	{
		return;
	}
	
	for (const FGameplayAbilitySpec AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
		
	}
	
}

void UPMAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}

void UPMAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FPMHeroAbilitySet> InDefaultTagGAs, const TArray<FPMHeroActionAbilitySet> InDefaultActionGAs,
	int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantAbilitySpecHandles)
{
	if (InDefaultTagGAs.IsEmpty() && InDefaultActionGAs.IsEmpty()) return;

	if (!InDefaultTagGAs.IsEmpty())
	{
		for (const FPMHeroAbilitySet& AbilitySet : InDefaultTagGAs)
		{
			if (!AbilitySet.IsValid()) continue;

			FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
			AbilitySpec.SourceObject = GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
			OutGrantAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
		}
	}

	if (!InDefaultActionGAs.IsEmpty())
	{
		for (const FPMHeroActionAbilitySet ActionAbilitySet : InDefaultActionGAs)
		{
			if (!ActionAbilitySet.IsValid()) continue;

			FGameplayAbilitySpec AbilitySpec(ActionAbilitySet.AbilityToGrant);
			AbilitySpec.SourceObject = GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(ActionAbilitySet.ActionTag);
		
			OutGrantAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
		}
	}
	
}

void UPMAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty()) return;

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}
