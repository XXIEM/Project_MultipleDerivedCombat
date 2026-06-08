// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Components/Combat/PawnCombatComponent.h"
#include "PM/Items/Weapons/PMWeaponBase.h"


#include "PM/PMDebugHelper.h"



void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, APMWeaponBase* InWeaponToRegister)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister),TEXT("A named named %s has already been added as carried weapon"),*InWeaponTagToRegister.ToString()); 
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister,InWeaponToRegister);

	// if (bRegisterAsEquippedWeapon)
	// {
	// 	CurrentEquippedWeaponTag = InWeaponTagToRegister;
	// }

	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"),*InWeaponToRegister->GetName(),*InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}

APMWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if(APMWeaponBase* const* FoundWeapon =  CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

APMWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::SetCurrentActionID(FName InActionID)
{
	if (InActionID.IsNone()) return;

	CurrentActionID = InActionID;
}

FName UPawnCombatComponent::GetCurrentActionID() const
{
	if (CurrentActionID.IsNone()) return FName();

	return CurrentActionID;
}

void UPawnCombatComponent::SetCurrentActionMontage(UAnimMontage* InActionMontage)
{
	if (InActionMontage == nullptr) return;

	CurrentActionMontage = InActionMontage;
}

UAnimMontage* UPawnCombatComponent::GetCurrentActionMontage() const
{
	if (CurrentActionMontage ==	nullptr) return nullptr;

	return CurrentActionMontage;
}

void UPawnCombatComponent::SetCurrentLockedEnemy(APMBaseCharacter* InTargetCharacter)
{
	if (InTargetCharacter == nullptr) return;

	CurrentLockedTarget = InTargetCharacter;
}

APMBaseCharacter* UPawnCombatComponent::GetCurrentLockedEnemy() const
{
	if (CurrentLockedTarget == nullptr) return nullptr;

	return CurrentLockedTarget;
}
