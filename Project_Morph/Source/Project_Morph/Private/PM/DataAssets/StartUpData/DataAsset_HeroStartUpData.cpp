// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/DataAssets/StartUpData/DataAsset_HeroStartUpData.h"

#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"



void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UPMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	
	for (const FPMHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		
		InASCToGive->GiveAbility(AbilitySpec);
		
	}
	
	
}
