// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../PMBaseAnimInstance.h"
#include "PMHeroLinkedAnimLayer.generated.h"


class UPMHeroAnimInstance;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMHeroLinkedAnimLayer : public UPMBaseAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UPMHeroAnimInstance* GetHeroAnimInstance() const;

	
};
