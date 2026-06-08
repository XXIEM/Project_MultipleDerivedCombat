// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Character/PMBaseCharacter.h"

#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/AbilitySystem/PMAttributeSet.h"
#include "PM/AbilitySystem/PMHealthSet.h"
#include "PM/Components/PMHealthComponent.h"

// Sets default values
APMBaseCharacter::APMBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	PMAbilitySystemComponent = CreateDefaultSubobject<UPMAbilitySystemComponent>(TEXT("PMAbilitySystemComponent"));

	HealthComponent=CreateDefaultSubobject<UPMHealthComponent>(TEXT("HealthComponent"));
	
}

UAbilitySystemComponent* APMBaseCharacter::GetAbilitySystemComponent() const
{
	return GetPMAbilitySystemComponent();
}

void APMBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (PMAbilitySystemComponent)
	{
		PMAbilitySystemComponent->InitAbilityActorInfo(this,this);
		HealthComponent->InitializeWithAbilitySystem(PMAbilitySystemComponent);
		ensureMsgf(!CharacterStartUpData.IsNull(),TEXT("Forgot to assign start up data to %s"),*GetName());
	}
	
}

void APMBaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass,Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),GetAbilitySystemComponent());

}

void APMBaseCharacter::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes,1.f);
}


