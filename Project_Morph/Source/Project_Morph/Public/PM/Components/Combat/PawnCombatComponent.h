// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PM/Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"


class APMBaseCharacter;
class APMWeaponBase;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	//用Tag注册武器
	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, APMWeaponBase* InWeaponToRegister);

	//根据Tag获取角色携带的武器
	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	APMWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	//当前装备武器的tag
	UPROPERTY(BlueprintReadWrite,Category = "PM|Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	//获取角色当前装备武器
	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	APMWeaponBase* GetCharacterCurrentEquippedWeapon() const;


public:
	
	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	void SetCurrentActionID(FName InActionID);

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	FName GetCurrentActionID() const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	void SetCurrentActionMontage(UAnimMontage* InActionMontage);

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	UAnimMontage* GetCurrentActionMontage() const;

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	void SetCurrentLockedEnemy(APMBaseCharacter* InTargetCharacter);

	UFUNCTION(BlueprintCallable,Category = "PM|Combat")
	APMBaseCharacter* GetCurrentLockedEnemy() const;
	
	
private:
	//CombatComponent携带的武器
	TMap<FGameplayTag,APMWeaponBase*> CharacterCarriedWeaponMap;

	//当前招式ID
	FName CurrentActionID;

	//当前招式蒙太奇（控制打断）
	UAnimMontage* CurrentActionMontage;

	//当前锁定的敌人
	APMBaseCharacter* CurrentLockedTarget;

	
};


