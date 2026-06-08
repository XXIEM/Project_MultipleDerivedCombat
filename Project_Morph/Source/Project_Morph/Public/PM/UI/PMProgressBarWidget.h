// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PM/UI/PMBaseUserWidget.h"
#include "PMProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMProgressBarWidget : public UPMBaseUserWidget
{
	GENERATED_BODY()
public:
	UPMProgressBarWidget();
protected:
	//UIWidget init
	void NativeConstruct() override;
private:
	void OnHealthFieldChanged(UObject* Object,UE::FieldNotification::FFieldId FieldId);
	void OnUnBalanceFieldChanged(UObject* Object,UE::FieldNotification::FFieldId FieldId);
	void OnStaminaFieldChanged(UObject* Object,UE::FieldNotification::FFieldId FieldId);
	
	UPROPERTY(meta=(BindWidget))
	class UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* UnBalanceProgressBar;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* StaminaProgressBar;
};
