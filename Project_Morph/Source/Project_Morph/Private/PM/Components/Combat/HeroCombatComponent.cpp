// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/Components/Combat/HeroCombatComponent.h"

#include "AbilitySystemComponent.h"
#include "PM/PMDebugHelper.h"
#include "PM/Items/Weapons/PMHeroWeapon.h"
#include "PM/AbilitySystem/Abilities/PMHeroGameplayAbility.h"
#include "PM/Character/PMHeroCharacter.h"

APMHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APMHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

APMHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<APMHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

void UHeroCombatComponent::InitHeroWeaponActionMap(APMHeroWeapon* InWeapon)
{
	if (!InWeapon) return;

	UDataTable* StratActionTable = InWeapon->HeroWeaponData.StartActionTable;
	UDataTable* DerivedActionTable = InWeapon->HeroWeaponData.DerivedActionTable;
	UDataTable* SpecialActionTable = InWeapon->HeroWeaponData.SpecialActionTable;

	//StartActionMap
	for (auto iter : StratActionTable->GetRowMap())
	{
		FName RowName = iter.Key;
		FStartActionTableStruct* DataTableRowInfo = (FStartActionTableStruct*)iter.Value;

		FGameplayTag InputTag = DataTableRowInfo->InputTag;
		bool bIsHighPriority = DataTableRowInfo->bIsHighPriority;
		FGameplayTag ActionGATag = DataTableRowInfo->ActionGATag;
		TPair<bool, FGameplayTag> ActionPair;
		ActionPair.Key = bIsHighPriority;
		ActionPair.Value = ActionGATag;
		
		StartActionMap.Emplace(InputTag,ActionPair);
	}
	

	//DerivedActionMap
	for (auto iter : DerivedActionTable->GetRowMap())
	{
		FName RowName = iter.Key;
		FDerivedActionTableStruct* DataTableRowInfo = (FDerivedActionTableStruct*)iter.Value;

		TArray<FName> PreActionID = DataTableRowInfo->PreActionID;
		FGameplayTag InputTag = DataTableRowInfo->InputTag;
		FGameplayTag ActionGATag = DataTableRowInfo->ActionGATag;

		for (FName CurPreActionID : PreActionID)
		{
			if (!DerivedActionMap.Contains(CurPreActionID))
			{
				TMap<FGameplayTag,FGameplayTag> TempMap;
				TempMap.Emplace(InputTag,ActionGATag);
				DerivedActionMap.Emplace(CurPreActionID,TempMap);
			}
			else
			{
				DerivedActionMap.Find(CurPreActionID)->Emplace(InputTag,ActionGATag);
			}
		}
		
	}

	//SpecialActionMap
	for (auto iter : SpecialActionTable->GetRowMap())
	{
		FName RowName = iter.Key;
		FSpecialActionTableStruct* DataTableRowInfo = (FSpecialActionTableStruct*)iter.Value;
		
		TArray<FName> PreActionID = DataTableRowInfo->PreActionID;
		FGameplayTag InputTag = DataTableRowInfo->InputTag;
		FGameplayTag SpecialJudgeTag = DataTableRowInfo->SpecialJudgeTag;
		FGameplayTag ActionGATag = DataTableRowInfo->ActionGATag;

		for (FName CurPreActionID : PreActionID)
		{
			if (!SpecialActionMap.Contains(CurPreActionID))
			{
				TPair<FGameplayTag, FGameplayTag> TempPair;
				TempPair.Key = SpecialJudgeTag;
				TempPair.Value = ActionGATag;
			
				TMap<FGameplayTag, TPair<FGameplayTag, FGameplayTag>> TempMap;
				TempMap.Emplace(InputTag,TempPair);
			
				SpecialActionMap.Emplace(CurPreActionID,TempMap);
			}
			else
			{
				TPair<FGameplayTag, FGameplayTag> TempPair;
				TempPair.Key = SpecialJudgeTag;
				TempPair.Value = ActionGATag;
			
				SpecialActionMap.Find(CurPreActionID)->Emplace(InputTag,TempPair);
			}
		}
	}

	//Debug
	DebugStartActionMap();
	DebugDerivedActionMap();
	DebugSpecialActionMap();

}

FGameplayTag UHeroCombatComponent::GetStartActionFromMap(FGameplayTag InputTag, bool& bIsHighPriority, bool& bSuccess) const
{
	if (!StartActionMap.Contains(InputTag))
	{
		bIsHighPriority = false;
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}

	TPair<bool, FGameplayTag> OutActionPair = *StartActionMap.Find(InputTag);
	if (OutActionPair == TPair<bool,FGameplayTag>())
	{
		bIsHighPriority = false;
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}
	else
	{
		bIsHighPriority = OutActionPair.Key;
		bSuccess = true;
		return OutActionPair.Value;
	}
}

FGameplayTag UHeroCombatComponent::GetDerivedActionFromMap(FName CurActionID,
	FGameplayTag InputTag, bool& bSuccess) const
{
	if (!DerivedActionMap.Contains(CurActionID))
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}

	TMap<FGameplayTag, FGameplayTag> CurMap = *DerivedActionMap.Find(CurActionID);
	if (!CurMap.Contains(InputTag))
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}

	FGameplayTag OutActionGATag = *CurMap.Find(InputTag);
	if (!OutActionGATag.IsValid())
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}
	else
	{
		bSuccess = true;
		return OutActionGATag;
	}
}

FGameplayTag UHeroCombatComponent::GetSpecialActionFromMap(FName CurActionID,
	FGameplayTag InputTag, bool& bSuccess) const
{
	if (!SpecialActionMap.Contains(CurActionID))
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}
	
	TMap<FGameplayTag,TPair<FGameplayTag,FGameplayTag>> CurMap = *SpecialActionMap.Find(CurActionID);
	if (!CurMap.Contains(InputTag))
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}
	
	TPair<FGameplayTag, FGameplayTag> OutActionPair = *CurMap.Find(InputTag);
	APMHeroCharacter* HeroOwner = Cast<APMHeroCharacter>(GetOwner());
	if (HeroOwner->GetAbilitySystemComponent()->HasMatchingGameplayTag(OutActionPair.Key))
	{
		bSuccess = true;
		return OutActionPair.Value;
	}
	else
	{
		bSuccess = false;
		return FGameplayTag::EmptyTag;
	}
}



//------------------------Debug（待删除）----------------------------------
void UHeroCombatComponent::DebugStartActionMap()
{
	UE_LOG(LogTemp, Warning, TEXT("===== StartActionMap Contents ====="));
	for (const auto& Pair : StartActionMap)
	{
		FString InputTagStr = Pair.Key.ToString();
		TPair<bool, FGameplayTag> ActionPair = Pair.Value;
		FString AbilityName = ActionPair.Value.GetTagName().ToString();
		FString IsHighPriority = ActionPair.Key ? FString(TEXT("true")) : FString(TEXT("false"));
		UE_LOG(LogTemp, Warning, TEXT("InputTag: %s -> Abilitytag: %s -> IsHighPriority: %s"), *InputTagStr, *AbilityName, *IsHighPriority);
	}
	UE_LOG(LogTemp, Warning, TEXT("================================"));
}

void UHeroCombatComponent::DebugDerivedActionMap()
{
	UE_LOG(LogTemp, Warning, TEXT("===== DerivedActionMap Contents ====="));
	for (const auto& OuterPair : DerivedActionMap)
	{
		FString PreActionID = OuterPair.Key.ToString();
		UE_LOG(LogTemp, Warning, TEXT("PreActionID: %s"), *PreActionID);
        
		for (const auto& InnerPair : OuterPair.Value)
		{
			FString InputTagStr = InnerPair.Key.ToString();
			FString AbilityName = InnerPair.Value.GetTagName().ToString();
			UE_LOG(LogTemp, Warning, TEXT("  InputTag: %s -> AbilityTag: %s"), *InputTagStr, *AbilityName);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("===================================="));
}

void UHeroCombatComponent::DebugSpecialActionMap()
{
	UE_LOG(LogTemp, Warning, TEXT("===== SpecialActionMap Contents ====="));
	for (const auto& OuterPair : SpecialActionMap)
	{
		FString PreActionID = OuterPair.Key.ToString();
		UE_LOG(LogTemp, Warning, TEXT("PreActionID: %s"), *PreActionID);
        
		for (const auto& MiddlePair : OuterPair.Value)
		{
			FString InputTagStr = MiddlePair.Key.ToString();
			UE_LOG(LogTemp, Warning, TEXT("  InputTag: %s"), *InputTagStr);
            
			const FGameplayTag& SpecialJudgeTag = MiddlePair.Value.Key;
			FGameplayTag Ability = MiddlePair.Value.Value;
			FString AbilityName = Ability.GetTagName().ToString();
			UE_LOG(LogTemp, Warning, TEXT("    SpecialJudgeTag: %s -> AbilityTag: %s"), 
				*SpecialJudgeTag.ToString(), *AbilityName);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("===================================="));
}
