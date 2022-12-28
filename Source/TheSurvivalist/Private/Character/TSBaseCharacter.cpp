// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSBaseCharacter.h"

#include "Camera/CameraComponent.h"

ATSBaseCharacter::ATSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
}

void ATSBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATSBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
