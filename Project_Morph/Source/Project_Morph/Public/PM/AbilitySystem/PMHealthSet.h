// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MVVMViewModelBase.h"
#include "PM/AbilitySystem/PMAttributeSet.h"
#include "PM/UI/ViewModel/HealthViewModel.h"
#include "PMHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMHealthSet : public UPMAttributeSet
{
	GENERATED_BODY()
public:
	UPMHealthSet();

	ATTRIBUTE_ACCESSORS(UPMHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UPMHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UPMHealthSet, UnBalance);
	ATTRIBUTE_ACCESSORS(UPMHealthSet, MaxUnBalance);
	ATTRIBUTE_ACCESSORS(UPMHealthSet, Stamina);
	ATTRIBUTE_ACCESSORS(UPMHealthSet, MaxStamina);

	mutable FPMAttributeEvent OnHealthChange;
	mutable FPMAttributeEvent OnMaxHealthChange;
	mutable FPMAttributeEvent OnOutOfHealth;

	mutable FPMAttributeEvent OnUnBalanceChange;
	mutable FPMAttributeEvent OnMaxUnBalanceChange;

	mutable FPMAttributeEvent OnStaminaChange;
	mutable FPMAttributeEvent OnMaxStaminaChange;

	// UFUNCTION()
	// UHealthViewModel* GetHealthViewModel() const;

	//UFUNCTION()
	//void ResetViewModel();

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_UnBalance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxUnBalance(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;
private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "PM|Health", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "PM|Health", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_UnBalance, Category = "PM|UnBalance", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData UnBalance;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxUnBalance, Category = "PM|UnBalance", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxUnBalance;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "PM|Stamina", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "PM|Stamina", meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	void ClampAttribute(const FGameplayAttribute& Attribute, float& newValue) const;
	bool bOutOfHealth;
	UPROPERTY()
	UHealthViewModel* HealthViewModel;
};
