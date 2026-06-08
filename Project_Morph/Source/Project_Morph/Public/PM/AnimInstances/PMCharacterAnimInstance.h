// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/AnimInstances/PMBaseAnimInstance.h"
#include "PMCharacterAnimInstance.generated.h"

class APMBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMCharacterAnimInstance : public UPMBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	APMBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category= "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category= "AnimData|LocomotionData")
	float Direction;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category= "AnimData|LocomotionData")
	bool bHasAcceleration;
	
};
