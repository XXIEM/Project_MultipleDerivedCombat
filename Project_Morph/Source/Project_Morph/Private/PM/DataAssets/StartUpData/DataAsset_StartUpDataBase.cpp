// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/AbilitySystem/Abilities/PMGameplayAbility.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UPMAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateAbilities,InASCToGive,ApplyLevel);
	GrantAbilities(ReactiveAbilities,InASCToGive,ApplyLevel);
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UPMGameplayAbility>>& InAbilitiesToGive,
	UPMAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for(const TSubclassOf<UPMGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
			
		InASCToGive->GiveAbility(AbilitySpec);
	}
}
