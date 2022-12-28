// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TSBaseCharacter.h"

ATSBaseCharacter::ATSBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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
