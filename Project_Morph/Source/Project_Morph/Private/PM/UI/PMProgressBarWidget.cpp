// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/UI/PMProgressBarWidget.h"

#include "Components/ProgressBar.h"
#include "PM/UI/ViewModel/HealthViewModel.h"

UPMProgressBarWidget::UPMProgressBarWidget()
{
	ViewModelClass=UHealthViewModel::StaticClass();
	ViewModelName = TEXT("HealthViewModel");
}

void UPMProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const auto VMInst = FindViewModel<UHealthViewModel>();
	VMInst->AddFieldValueChangedDelegate(UHealthViewModel::FFieldNotificationClassDescriptor::CurrentHealth,FFieldValueChangedDelegate::CreateUObject(this,&UPMProgressBarWidget::OnHealthFieldChanged));
	VMInst->AddFieldValueChangedDelegate(UHealthViewModel::FFieldNotificationClassDescriptor::CurrentUnBalance,FFieldValueChangedDelegate::CreateUObject(this,&UPMProgressBarWidget::OnUnBalanceFieldChanged));
	VMInst->AddFieldValueChangedDelegate(UHealthViewModel::FFieldNotificationClassDescriptor::CurrentStamina,FFieldValueChangedDelegate::CreateUObject(this,&UPMProgressBarWidget::OnStaminaFieldChanged));
}

void UPMProgressBarWidget::OnHealthFieldChanged(UObject* Object, UE::FieldNotification::FFieldId FieldId)
{
	const auto VM=FindViewModel<UHealthViewModel>();
	UE_LOG(LogTemp, Log, TEXT("ProgressWidget CurrentHealth changed - new percent '%f' "), VM->GetHealthPercent());
	HealthProgressBar->SetPercent(VM->GetHealthPercent());
}

void UPMProgressBarWidget::OnUnBalanceFieldChanged(UObject* Object, UE::FieldNotification::FFieldId FieldId)
{
	const auto VM=FindViewModel<UHealthViewModel>();
	UE_LOG(LogTemp, Log, TEXT("ProgressWidget CurrentUnBalance changed - new percent '%f' "), VM->GetUnBalancePercent());
	UnBalanceProgressBar->SetPercent(VM->GetUnBalancePercent());
}

void UPMProgressBarWidget::OnStaminaFieldChanged(UObject* Object, UE::FieldNotification::FFieldId FieldId)
{
	const auto VM=FindViewModel<UHealthViewModel>();
	UE_LOG(LogTemp, Log, TEXT("ProgressWidget CurrentStamina changed - new percent '%f' "), VM->GetStaminaPercent());
	StaminaProgressBar->SetPercent(VM->GetStaminaPercent());
}
