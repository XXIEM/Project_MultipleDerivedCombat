// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "PM/PMTypes/PMStructTypes.h"
#include "DataAsset_HeroStartUpData.generated.h"



/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UPMAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;

	
private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta=(TitleProperty = "InputTag"))
	TArray<FPMHeroAbilitySet> HeroStartUpAbilitySets;
	
};
