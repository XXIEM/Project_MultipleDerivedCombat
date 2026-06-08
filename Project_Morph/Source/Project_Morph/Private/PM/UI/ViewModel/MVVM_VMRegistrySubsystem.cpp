// Fill out your copyright notice in the Description page of Project Settings.


#include "PM/UI/ViewModel/MVVM_VMRegistrySubsystem.h"

#include "MVVMGameSubsystem.h"
#include "PM/UI/ViewModel/HealthViewModel.h"

void UMVVM_VMRegistrySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Collection.InitializeDependency(UMVVMGameSubsystem::StaticClass());

	RegisterViewModels();
}

void UMVVM_VMRegistrySubsystem::RegisterViewModels()
{
	const auto MVVMCollection = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();
	AddViewModel(MVVMCollection, UHealthViewModel::StaticClass(), FName("HealthViewModel"));

}

void UMVVM_VMRegistrySubsystem::AddViewModel(UMVVMViewModelCollectionObject* VMCollection,
	const TSubclassOf<UMVVMViewModelBase>& ViewModelClass, FName ViewModelUniqueIdentifier)
{
	FMVVMViewModelContext ViewModelContext;
	ViewModelContext.ContextName = ViewModelUniqueIdentifier;
	ViewModelContext.ContextClass = ViewModelClass;

	const auto VMInstance = NewObject<UMVVMViewModelBase>(this, ViewModelClass);
	VMCollection->AddViewModelInstance(ViewModelContext, VMInstance);
}
