// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSBaseCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

ATSBaseCharacter::ATSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = true;
}

void ATSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveForwardsAction, ETriggerEvent::Triggered, this, &ATSBaseCharacter::MoveForwards);
		EIC->BindAction(MoveForwardsAction, ETriggerEvent::Completed, this, &ATSBaseCharacter::MoveForwards);
		
		EIC->BindAction(MoveSidewaysAction, ETriggerEvent::Triggered, this, &ATSBaseCharacter::MoveSideways);
		EIC->BindAction(MoveSidewaysAction, ETriggerEvent::Completed, this, &ATSBaseCharacter::MoveSideways);
		
		EIC->BindAction(TurnRightAction, ETriggerEvent::Triggered, this, &ATSBaseCharacter::TurnRight);
		EIC->BindAction(TurnRightAction, ETriggerEvent::Completed, this, &ATSBaseCharacter::TurnRight);

		EIC->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &ATSBaseCharacter::LookUp);
		EIC->BindAction(LookUpAction, ETriggerEvent::Completed, this, &ATSBaseCharacter::LookUp);

		EIC->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
}

void ATSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(const APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMovementMappingContext, 0);
		}
	}
}

void ATSBaseCharacter::MoveForwards(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector(), Value.Get<float>());
}

void ATSBaseCharacter::MoveSideways(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector(), Value.Get<float>());
}

void ATSBaseCharacter::LookUp(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.Get<float>());
}

void ATSBaseCharacter::TurnRight(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.Get<float>());
}
