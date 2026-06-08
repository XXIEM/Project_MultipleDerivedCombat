// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PM/Character/PMBaseCharacter.h"
#include "PMHeroCharacter.generated.h"

class UHealthViewModel;
class USpringArmComponent;
class UCameraComponent;
class UDataAsset_InputConfig;
struct FInputActionValue;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API APMHeroCharacter : public APMBaseCharacter
{
	GENERATED_BODY()

public:
	APMHeroCharacter();
	FORCEINLINE UHeroCombatComponent* GetHeroCombatComponent() const {return HeroCombatComponent;}
	// UFUNCTION(BlueprintCallable)
	// UHealthViewModel* GetHealthViewModel();

	

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
	
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	

private:
#pragma region Components

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Combat", meta=(AllowPrivateAccess = "true"))
	UHeroCombatComponent* HeroCombatComponent;
		
#pragma endregion

#pragma region Inputs
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "CharacterData", meta=(AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_StopMoving();
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
	
#pragma endregion

	void InitAbilityActorInfo();

	
	UPROPERTY()
	UHealthViewModel* HealthViewModel;
	
};
