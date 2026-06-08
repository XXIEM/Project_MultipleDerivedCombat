// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/AnimInstances/Player/PMHeroLinkedAnimLayer.h"
#include "PM/AnimInstances/Player/PMHeroAnimInstance.h"

UPMHeroAnimInstance* UPMHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UPMHeroAnimInstance>(GetOwningComponent()->GetAnimInstance()); 
}
