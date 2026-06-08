// Fill out your copyright notice in the Description page of Project Settings.


#include "PM\Character\PMHeroCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PM/DataAssets/Input/DataAsset_InputConfig.h"
#include "PM/Components/Input/PMInputComponent.h"
#include "PM/PMGameplayTags.h"
#include "PM/AbilitySystem/PMAbilitySystemComponent.h"
#include "PM/DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "PM/Components/Combat/HeroCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MVVMGameSubsystem.h"


#include "PM/PMDebugHelper.h"
#include "PM/AbilitySystem/PMHealthSet.h"
#include "PM/UI/ViewModel/HealthViewModel.h"
#include "Types/MVVMViewModelContext.h"


APMHeroCharacter::APMHeroCharacter()
{
	//GetCapsuleComponent()->InitCapsuleSize(42.f,96.f);
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bReplicates=true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f,55.f,65.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));
	
}



void APMHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!CharacterStartUpData.IsNull())
	{
		if(UDataAsset_StartUpDataBase* LoadedData =  CharacterStartUpData.LoadSynchronous())
		{
			LoadedData->GiveToAbilitySystemComponent(PMAbilitySystemComponent);
		}
	}
	
}

void APMHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"))
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);

	UPMInputComponent* PMInputComponent = CastChecked<UPMInputComponent>(PlayerInputComponent);

	//绑定初始输入
	PMInputComponent->BindNativeInputAction(InputConfigDataAsset,PMGameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	PMInputComponent->BindNativeInputAction(InputConfigDataAsset,PMGameplayTags::InputTag_Move,ETriggerEvent::Completed,this,&ThisClass::Input_StopMoving);
	PMInputComponent->BindNativeInputAction(InputConfigDataAsset,PMGameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);

	//绑定能力输入
	PMInputComponent->BindAbilityInputAction(InputConfigDataAsset,this,&ThisClass::Input_AbilityInputPressed,&ThisClass::Input_AbilityInputReleased);
	
}

void APMHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	//PMHealthSet->ResetViewModel();
	UE_LOG(LogTemp, Warning, TEXT("reset"));
	InitializeDefaultAttributes();
}

void APMHeroCharacter::InitAbilityActorInfo()
{
	
}

// UHealthViewModel* APMHeroCharacter::GetHealthViewModel()
// {
// 	if(!HealthViewModel)
// 	{
// 		const auto Collection = GetGameInstance()->GetSubsystem<UMVVMGameSubsystem>()->GetViewModelCollection();
// 		FMVVMViewModelContext VMContext;
// 		VMContext.ContextName = FName("HealthViewModel");
// 		VMContext.ContextClass = UHealthViewModel::StaticClass();
// 		const auto VMInstance = Collection->FindViewModelInstance(VMContext);
// 		HealthViewModel=Cast<UHealthViewModel>(VMInstance);
// 		
// 	}
// 	return  HealthViewModel;
// }

void APMHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2d MovementVector = InputActionValue.Get<FVector2d>();
	const FRotator MovementRotation(0.f,Controller->GetControlRotation().Yaw,0.f);

	if(MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection,MovementVector.Y);
	}

	if(MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection,MovementVector.X);
		
	}

	if (!PMAbilitySystemComponent->HasMatchingGameplayTag(PMGameplayTags::PM_State_Action_IsMoving))
	{
		PMAbilitySystemComponent->AddLooseGameplayTag(PMGameplayTags::PM_State_Action_IsMoving);
	}
	
}

void APMHeroCharacter::Input_StopMoving()
{
	//IsMoving的Tag标记
	if (PMAbilitySystemComponent->HasMatchingGameplayTag(PMGameplayTags::PM_State_Action_IsMoving))
	{
		PMAbilitySystemComponent->RemoveLooseGameplayTag(PMGameplayTags::PM_State_Action_IsMoving);
	}
	
}

void APMHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2d LookAxisVector = InputActionValue.Get<FVector2d>();
	
	if(LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	
	if(LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
	
	
}

void APMHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	if (InInputTag.MatchesTag(PMGameplayTags::InputTag_Attack))
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetPMAbilitySystemComponent()->GetAvatarActor();
		Payload.EventTag = InInputTag;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this,InInputTag,Payload);
	}
	else
	{
		PMAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
	}
}

void APMHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	PMAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}

