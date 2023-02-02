// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionArea/NPIM_InteractionArea_Box.h"

#include "Components/BoxComponent.h"

ANPIM_InteractionArea_Box::ANPIM_InteractionArea_Box()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(RootComponent);
	Box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}