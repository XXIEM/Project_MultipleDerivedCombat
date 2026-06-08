// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AbilitySystem/PMHealthSet.h"

#include "Net/UnrealNetwork.h"
#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/Character/PMEnemyCharacter.h"
#include "PM/Character/PMHeroCharacter.h"

UPMHealthSet::UPMHealthSet()
	: Health(0.f)
	, MaxHealth(0.f)
{
	bOutOfHealth=false;
}

// UHealthViewModel* UPMHealthSet::GetHealthViewModel() const
// {
// 	return HealthViewModel;
// }
//
// void UPMHealthSet::ResetViewModel()
// {
//
// 	UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent();
// 	if (!ASC)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is not available."));
// 		return;
// 	}
//
// 	APMHeroCharacter* Character = Cast<APMHeroCharacter>(ASC->GetOwnerActor());
// 	if (!Character)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Failed to cast to APMHeroCharacter."));
// 		return;
// 	}
//
// 	HealthViewModel = Character->GetHealthViewModel();
//
// }
void UPMHealthSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	UE_LOG(LogTemp, Warning, TEXT("set current health"));
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,Health,OldValue);
	const float CurrentHealth = GetHealth();
	// the num of change.
	const float EstimatedMagnitude = CurrentHealth-OldValue.GetCurrentValue();
	
	OnHealthChange.Broadcast(nullptr,nullptr,nullptr,EstimatedMagnitude,OldValue.GetCurrentValue(),CurrentHealth);
	//HealthViewModel->SetCurrentHealth(CurrentHealth);
	if(!bOutOfHealth&&CurrentHealth<0)
	{
		OnOutOfHealth.Broadcast(nullptr,nullptr,nullptr,EstimatedMagnitude,OldValue.GetCurrentValue(),CurrentHealth);
		bOutOfHealth=true;
	}
}

void UPMHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	UE_LOG(LogTemp, Warning, TEXT("set maxhealth"));
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,MaxHealth,OldValue);
	
	OnMaxHealthChange.Broadcast(nullptr,nullptr,nullptr,GetMaxHealth()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetMaxHealth());
	//HealthViewModel->SetMaxHealth(GetMaxHealth());
}

void UPMHealthSet::OnRep_UnBalance(const FGameplayAttributeData& OldValue)
{
	// 获取当前角色的引用
	auto OwningCharacter = GetOwningActor();

	// 检查角色是否是 HeroCharacter 类型
	if (OwningCharacter && OwningCharacter->IsA<APMEnemyCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("set UnBalance"));
		GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,UnBalance,OldValue);
	
		OnUnBalanceChange.Broadcast(nullptr,nullptr,nullptr,GetUnBalance()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetUnBalance());
		//HealthViewModel->SetCurrentUnBalance(GetUnBalance());
	}
}

void UPMHealthSet::OnRep_MaxUnBalance(const FGameplayAttributeData& OldValue) const
{	// 获取当前角色的引用
	auto OwningCharacter = GetOwningActor();

	// 检查角色是否是 HeroCharacter 类型
	if (OwningCharacter && OwningCharacter->IsA<APMEnemyCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("set maxUnBalance"));
		GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,MaxUnBalance,OldValue);
	
		OnMaxUnBalanceChange.Broadcast(nullptr,nullptr,nullptr,GetMaxUnBalance()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetMaxUnBalance());
		//HealthViewModel->SetMaxUnBalance(GetMaxUnBalance());
	}
}

void UPMHealthSet::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	// 获取当前角色的引用
	auto OwningCharacter = GetOwningActor();

	// 检查角色是否是 HeroCharacter 类型
	if (OwningCharacter && OwningCharacter->IsA<APMHeroCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("set Stamina"));
		GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,Stamina,OldValue);
	
		OnStaminaChange.Broadcast(nullptr,nullptr,nullptr,GetStamina()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetStamina());
		//HealthViewModel->SetCurrentStamina(GetStamina());
	}
}

void UPMHealthSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const
{
	// 获取当前角色的引用
	auto OwningCharacter = GetOwningActor();

	// 检查角色是否是 HeroCharacter 类型
	if (OwningCharacter && OwningCharacter->IsA<APMHeroCharacter>())
	{
		UE_LOG(LogTemp, Warning, TEXT("set maxStamina"));
		GAMEPLAYATTRIBUTE_REPNOTIFY(UPMHealthSet,MaxStamina,OldValue);
	
		OnMaxStaminaChange.Broadcast(nullptr,nullptr,nullptr,GetMaxStamina()-OldValue.GetCurrentValue(),OldValue.GetCurrentValue(),GetMaxStamina());
		//HealthViewModel->SetMaxStamina(GetMaxStamina());
	}
}

void UPMHealthSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	ClampAttribute(Attribute,NewValue);

}

void UPMHealthSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	UE_LOG(LogTemp, Warning, TEXT("PostAttributeChange CurrentHealth changed - new value %f, "),OldValue );
	UE_LOG(LogTemp, Warning, TEXT("PostAttributeChange CurrentHealth changed - new value %s, "),*Attribute.GetName());
	auto OwningCharacter = GetOwningActor();

	// 检查角色是否是 HeroCharacter 类型
	// if (Attribute==GetHealthAttribute())
	// {
	// 	HealthViewModel->SetMaxHealth(GetMaxHealth());
	// 	HealthViewModel->SetCurrentHealth(GetHealth());
	// }
	// if (OwningCharacter && OwningCharacter->IsA<APMEnemyCharacter>()&&(Attribute==GetUnBalanceAttribute()||Attribute==GetMaxUnBalanceAttribute()))
	// {
	// 	
	// 	HealthViewModel->SetMaxUnBalance(GetMaxUnBalance());
	// 	HealthViewModel->SetCurrentUnBalance(GetUnBalance());
	// }
	// if (OwningCharacter && OwningCharacter->IsA<APMHeroCharacter>()&&Attribute==GetStaminaAttribute())
	// {
	// 	HealthViewModel->SetMaxStamina(GetMaxStamina());
	// 	HealthViewModel->SetCurrentStamina(GetStamina());
	// }

	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if(Attribute==GetMaxHealthAttribute()&&NewValue<GetHealth())
	{
		
		UPMAbilitySystemComponent* PMASC = GetPMAbilitySystemComponent();
		check(PMASC);
		PMASC->ApplyModToAttribute(GetHealthAttribute(),EGameplayModOp::Override,NewValue);
		
	}
	
	if(bOutOfHealth&&GetHealth()>0.f)
	{
		bOutOfHealth=false;
	}
}

void UPMHealthSet::ClampAttribute(const FGameplayAttribute& Attribute, float& newValue) const
{
	if(Attribute==GetHealthAttribute())
	{
		newValue = FMath::Clamp(newValue,0,GetMaxHealth());
	}else if(Attribute==GetMaxHealthAttribute())
	{
		newValue = FMath::Max(newValue,1.f);
	}

	if(Attribute==GetStaminaAttribute())
	{
		newValue = FMath::Clamp(newValue,0, GetMaxStamina());
	}else if(Attribute==GetMaxStaminaAttribute())
	{
		newValue = FMath::Max(newValue,1.f);
	}

	if(Attribute==GetUnBalanceAttribute())
	{
		newValue = FMath::Clamp(newValue,0,GetMaxUnBalance());
	}else if(Attribute==GetMaxStaminaAttribute())
	{
		newValue = FMath::Max(newValue,1.f);
	}
	
}

void UPMHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPMHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPMHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
	UE_LOG(LogTemp, Warning, TEXT("11"));

}
