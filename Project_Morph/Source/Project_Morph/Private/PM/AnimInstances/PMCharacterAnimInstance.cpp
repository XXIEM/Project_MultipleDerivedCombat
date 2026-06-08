         // Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AnimInstances/PMCharacterAnimInstance.h"


#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PM/Character/PMBaseCharacter.h"



void UPMCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<APMBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UPMCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;		
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	Direction = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(),OwningCharacter->GetActorRotation());
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
}
