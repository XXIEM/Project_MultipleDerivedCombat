// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_MORPH_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()
	
protected:

	//可以指定T类型方便获取特定类型的Pawn
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,APawn>::Value,"'T' Template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	//不指定T类型默认返回APawn
	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	//可以指定T类型方便获取特定类型的Controller
	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T,AController>::Value,"'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
};
