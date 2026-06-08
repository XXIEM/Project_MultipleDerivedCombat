// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/UI/PMHUD.h"

#include "Blueprint/UserWidget.h"
#include "PM/UI/PMBaseUserWidget.h"

void APMHUD::BeginPlay()
{
	Super::BeginPlay();
    UPMBaseUserWidget* Widget = CreateWidget<UPMBaseUserWidget>(GetWorld(),OverlayWidgetClass);
    Widget->AddToViewport();
}
