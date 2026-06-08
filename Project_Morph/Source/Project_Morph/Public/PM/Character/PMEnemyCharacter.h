// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/Character/PMBaseCharacter.h"
#include "PMEnemyCharacter.generated.h"

class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API APMEnemyCharacter : public APMBaseCharacter
{
	GENERATED_BODY()

public:
	APMEnemyCharacter();


	
protected:
		//~ Begin APawn Interface.
		virtual void PossessedBy(AController* NewController) override;
		//~ End APawn Interface
	
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		UEnemyCombatComponent* EnemyCombatComponent;

	virtual void BeginPlay() override;
	 
private:
	void InitEnemyStartUpData();
	
public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;}
};
