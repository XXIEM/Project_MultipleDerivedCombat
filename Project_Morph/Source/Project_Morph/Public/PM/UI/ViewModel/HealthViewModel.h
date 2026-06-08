// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "HealthViewModel.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UHealthViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	void SetMaxHealth(int32 InMaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetMaxHealth MaxHealth changed - new percent %d"),InMaxHealth );
		if(UE_MVVM_SET_PROPERTY_VALUE(MaxHealth,InMaxHealth))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
		}
	}

	void SetCurrentHealth(int32 InCurrentHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCurrentHealth CurrentHealth changed - new percent %d"),InCurrentHealth );
		if(UE_MVVM_SET_PROPERTY_VALUE(CurrentHealth,InCurrentHealth))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetHealthPercent);
		}

	}

	void SetMaxUnBalance(int32 InMaxUnBalance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetMaxUnBalance MaxUnBalance changed - new percent %d"),InMaxUnBalance );
		if(UE_MVVM_SET_PROPERTY_VALUE(MaxUnBalance,InMaxUnBalance))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetUnBalancePercent);
		}
	}

	void SetCurrentUnBalance(int32 InCurrentUnBalance)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCurrentUnBalance CurrentUnBalance changed - new percent %d"),InCurrentUnBalance );
		if(UE_MVVM_SET_PROPERTY_VALUE(CurrentUnBalance,InCurrentUnBalance))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetUnBalancePercent);
		}

	}

	void SetMaxStamina(int32 InMaxStamina)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetMaxStamina MaxStamina changed - new percent %d"),InMaxStamina );
		if(UE_MVVM_SET_PROPERTY_VALUE(MaxStamina,InMaxStamina))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		}
	}

	void SetCurrentStamina(int32 InCurrentStamina)
	{
		UE_LOG(LogTemp, Warning, TEXT("SetCurrentStamina CurrentStamina changed - new percent %d"),InCurrentStamina );
		if(UE_MVVM_SET_PROPERTY_VALUE(CurrentStamina,InCurrentStamina))
		{
			UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(GetStaminaPercent);
		}

	}
	UFUNCTION(BlueprintPure,FieldNotify)
	float GetHealthPercent() const
	{
		UE_LOG(LogTemp, Warning, TEXT("GetHealthPercent  changed - new percent %f"),(float)CurrentHealth/(float)MaxHealth );
		if(MaxHealth>0)
		{
			return (float)CurrentHealth/(float)MaxHealth;
		}
		return 0;
	}

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetUnBalancePercent() const
	{
		UE_LOG(LogTemp, Warning, TEXT("GetUnBalancePercent  changed - new percent %f"),(float)CurrentUnBalance/(float)MaxUnBalance );
		if(MaxUnBalance>0)
		{
			return (float)CurrentUnBalance/(float)MaxUnBalance;
		}
		return 0;
	}

	UFUNCTION(BlueprintPure,FieldNotify)
	float GetStaminaPercent() const
	{
		UE_LOG(LogTemp, Warning, TEXT("GetStaminaPercent  changed - new percent %f"),(float)CurrentStamina/(float)MaxStamina );
		if(MaxStamina>0)
		{
			return (float)CurrentStamina/(float)MaxStamina;
		}
		return 0;
	}
	
private:
	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 CurrentHealth = 0.f;

	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 MaxHealth = 0.f;
	
	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 CurrentUnBalance = 0.f;

	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 MaxUnBalance = 0.f;

	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 CurrentStamina = 0.f;

	UPROPERTY(BlueprintReadOnly,Setter,FieldNotify,meta=(AllowPrivateAccess))
	int32 MaxStamina = 0.f;

};
