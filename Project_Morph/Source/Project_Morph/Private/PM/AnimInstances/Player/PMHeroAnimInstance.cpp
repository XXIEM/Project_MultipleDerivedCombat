// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AnimInstances/Player/PMHeroAnimInstance.h"
#include "PM/Character/PMHeroCharacter.h"

void UPMHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if(OwningCharacter)
	{
		OwningHeroCharacter = Cast<APMHeroCharacter>(OwningCharacter);
	}
}
