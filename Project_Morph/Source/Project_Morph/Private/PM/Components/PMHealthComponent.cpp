// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Components/PMHealthComponent.h"

#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/AbilitySystem/PMHealthSet.h"

// Sets default values for this component's properties
UPMHealthComponent::UPMHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
	DeathState = EPMDeathState::NotDead;
}

void UPMHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void UPMHealthComponent::InitializeWithAbilitySystem(UPMAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	AbilitySystemComponent = InASC;

	HealthSet=AbilitySystemComponent->GetSet<UPMHealthSet>();

	//Register to listen for attribute changes.
	HealthSet->OnHealthChange.AddUObject(this,&ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChange.AddUObject(this,&ThisClass::HandleMaxHealthChanged);


	//AbilitySystemComponent->SetNumericAttributeBase(UPMHealthSet::GetHealthAttribute(),HealthSet->GetMaxHealth());

	//ClearGameplayTags();

	OnHealthChanged.Broadcast(this,HealthSet->GetHealth(),HealthSet->GetHealth(),nullptr);
	OnMaxHealthChanged.Broadcast(this,HealthSet->GetHealth(),HealthSet->GetHealth(),nullptr);
	
}

void UPMHealthComponent::UninitializeFromAbilitySystem()
{
	ClearGameplayTags();

	if(HealthSet)
	{
		HealthSet->OnHealthChange.RemoveAll(this);
		HealthSet->OnMaxHealthChange.RemoveAll(this);
	}

	HealthSet=nullptr;
	AbilitySystemComponent=nullptr;
}

float UPMHealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);

}

float UPMHealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);

}

float UPMHealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();

		return ((MaxHealth > 0.0f) ? (Health / MaxHealth) : 0.0f);
	}

	return 0.0f;
}

void UPMHealthComponent::StartDeath()
{
}

void UPMHealthComponent::FinishDeath()
{
}

void UPMHealthComponent::OnUnregister()
{
	Super::OnUnregister();
}

void UPMHealthComponent::ClearGameplayTags()
{
}

void UPMHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
		OnHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);

}

void UPMHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);

}

void UPMHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
}

void UPMHealthComponent::OnRep_DeathState(EPMDeathState OldDeathState)
{
}
