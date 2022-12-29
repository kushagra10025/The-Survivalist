// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/InteractionArea/ISInteractionArea.h"

#include "Components/BoxComponent.h"

AISInteractionArea::AISInteractionArea()
{
	PrimaryActorTick.bCanEverTick = true;

	ActorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorRoot"));
	SetRootComponent(ActorRoot);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

}

void AISInteractionArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AISInteractionArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AISInteractionArea::ToggleFocus(bool NewFocused)
{
	bFocused = NewFocused;
}

