// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MVVMGameSubsystem.h"
#include "PMBaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_MORPH_API UPMBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FName ViewModelName;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UMVVMViewModelBase> ViewModelClass;

	template<typename VMClass>
	VMClass* FindViewModel() const
	{
		const auto Collection = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();
		FMVVMViewModelContext VMContext;
		VMContext.ContextName = ViewModelName;
		VMContext.ContextClass = ViewModelClass;
		const auto VMInstance = Collection->FindViewModelInstance(VMContext);
		if(IsValid(VMInstance))
		{
			return Cast<VMClass>(VMInstance);
		}
		checkf(false,TEXT("Unable to find a ViewModel that matches the give VMname and VMclass"));
		return nullptr;
	}
};
