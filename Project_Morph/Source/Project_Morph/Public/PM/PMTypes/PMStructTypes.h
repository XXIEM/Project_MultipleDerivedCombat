// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameplayTagContainer.h"


#include "PMStructTypes.generated.h"

class UPMHeroGameplayAbility;
class UPMHeroLinkedAnimLayer;
class UPMGameplayAbility;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FPMHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UPMGameplayAbility> AbilityToGrant;

	bool IsValid() const;
	
};

USTRUCT(BlueprintType)
struct FPMHeroActionAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (Categories = "ActionTag"))
	FGameplayTag ActionTag;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UPMGameplayAbility> AbilityToGrant;

	bool IsValid() const;
	
};


//----------------- Datatable ----------------
USTRUCT(BlueprintType)
struct  FStartActionTableStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	//招式名称
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName ActionName; 

	//触发所需输入Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; 

	//招式GA
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta = (Categories = "ActionTag"))
	FGameplayTag ActionGATag; 

	//招式描述
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite) 
	FName Description;

	//是否为高优先级招式
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	bool bIsHighPriority;

};

USTRUCT(BlueprintType)
struct  FDerivedActionTableStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	//前置招式ID
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<FName> PreActionID;

	//招式名称
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName ActionName; 

	//触发所需输入Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag; 

	//招式GATag
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta = (Categories = "ActionTag"))
	FGameplayTag ActionGATag; 

	//招式描述
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite) 
	FName Description; 

};

USTRUCT(BlueprintType)
struct  FSpecialActionTableStruct :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	//前置招式ID
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<FName> PreActionID;

	//招式名称
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	FName ActionName;

	//触发所需输入Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	//前置特殊判定Tag
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag SpecialJudgeTag;

	//招式GATag
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, meta = (Categories = "ActionTag"))
	FGameplayTag ActionGATag; 

	//招式描述
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite) 
	FName Description; 

};



//----------------- Weapon ----------------

USTRUCT(BlueprintType)
struct FPMHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UPMHeroLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext;

	/**
	 用InputTag可以直接驱动的GA
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(TitleProperty = "InputTag"))
	TArray<FPMHeroAbilitySet> DefaultTagGAs;

	/**
	 武器自己的招式GA
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FPMHeroActionAbilitySet> DefaultActionGAs;

	//招式表
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Datatable")
	UDataTable* StartActionTable;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Datatable")
	UDataTable* DerivedActionTable;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Datatable")
	UDataTable* SpecialActionTable;
	
};