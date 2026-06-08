// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PMAttributeSet.generated.h"

/**
 * 
 */
//define a set of helper function for accessing and initializing attributes. 
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// #define SYNC_VIEW_MODEL_BEGIN(PropertyName)\
// 	if(Attribute==Get##PropertyName##Attribute())\
// 	{\
// 		ViewModel->Set##PropertyName(Value));\
// 	}
class UPMAbilitySystemComponent;
struct FGameplayEffectSpec;
DECLARE_MULTICAST_DELEGATE_SixParams(FPMAttributeEvent, AActor* /*EffectInstigator*/,
	AActor* /*EffectCauser*/,
	const FGameplayEffectSpec*/*EffectSpec*/,
	float /*EffectMagnitude*/,
	float/*OldValue*/,
	float/*NewValue*/);
//Base attribute set class.
UCLASS()
class PROJECT_MORPH_API UPMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPMAbilitySystemComponent* GetPMAbilitySystemComponent() const;
};
