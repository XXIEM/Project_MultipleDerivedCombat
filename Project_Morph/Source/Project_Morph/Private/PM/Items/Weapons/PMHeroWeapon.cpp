// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Items/Weapons/PMHeroWeapon.h"

#include "GameplayAbilitySpec.h"
#include "PM/AbilitySystem/PMAbilitySystemComponent.h"

void APMHeroWeapon::AssignGrantedAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	GrantedAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> APMHeroWeapon::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}

FGameplayAbilitySpecHandle APMHeroWeapon::GetGrantedActionAbilitySpecHandle(UPMAbilitySystemComponent* ASC, FGameplayTag InActionTag) const
{
	for (const FGameplayAbilitySpecHandle& SpecHandle : GrantedAbilitySpecHandles)
	{
		FGameplayAbilitySpec AbilitySpec = *ASC->FindAbilitySpecFromHandle(SpecHandle);
		
		
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InActionTag)) continue;
		UE_LOG(LogTemp, Warning, TEXT("AbilitySpec GA: %s -> AbilitySpec DynamicTag: %s"), *AbilitySpec.Ability.GetName(), *AbilitySpec.DynamicAbilityTags.ToString());
		return SpecHandle;
	}
	return FGameplayAbilitySpecHandle();
}
