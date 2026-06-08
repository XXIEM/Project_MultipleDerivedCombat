// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "PMBaseCharacter.generated.h"


class UPMHealthComponent;
class UPMHealthSet;
class UGameplayEffect;
class UPMAbilitySystemComponent;
class UPMAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class PROJECT_MORPH_API APMBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APMBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	
	FORCEINLINE UPMAbilitySystemComponent* GetPMAbilitySystemComponent()const{return PMAbilitySystemComponent;}

	FORCEINLINE UPMHealthSet* GetPMHealthSet()const {return PMHealthSet;}

protected:

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "AbilitySystem")
	UPMAbilitySystemComponent* PMAbilitySystemComponent;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category = "AbilitySystem")
	UPMHealthSet* PMHealthSet;

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category = "AbilitySystem")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass,float Level) const;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

	void InitializeDefaultAttributes() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPMHealthComponent> HealthComponent;
};
