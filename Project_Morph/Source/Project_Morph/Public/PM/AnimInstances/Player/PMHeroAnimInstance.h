// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\PMCharacterAnimInstance.h"
#include "PMHeroAnimInstance.generated.h"

class APMHeroCharacter;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMHeroAnimInstance : public UPMCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

protected:
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="AnimData|Refrences")
	APMHeroCharacter* OwningHeroCharacter;
	
};
