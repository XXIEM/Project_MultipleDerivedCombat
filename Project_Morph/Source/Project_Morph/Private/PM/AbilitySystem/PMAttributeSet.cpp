// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/PMAttributeSet.h"

#include "PM/AbilitySystem/PMAbilitySystemComponent.h"

UPMAbilitySystemComponent* UPMAttributeSet::GetPMAbilitySystemComponent() const
{
	return Cast<UPMAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}
