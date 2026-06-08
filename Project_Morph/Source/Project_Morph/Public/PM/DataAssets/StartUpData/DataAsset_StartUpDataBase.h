// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UPMGameplayAbility;
class UPMAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UPMAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPMGameplayAbility>> ActivateAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UPMGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UPMGameplayAbility>>& InAbilitiesToGive, UPMAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
