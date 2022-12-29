// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem/ISACInteractionTrace.h"

#include "InteractionSystem/InteractionArea/ISInteractionArea.h"
#include "Kismet/GameplayStatics.h"


UISACInteractionTrace::UISACInteractionTrace():
	TraceLength(400.f)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetComponentTickInterval(0.03f);
}

void UISACInteractionTrace::TickComponent(float DeltaTime, ELevelTick TickType,
										  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Trace(DeltaTime);
}

void UISACInteractionTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void UISACInteractionTrace::Trace(float DeltaTime)
{
	if(APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		const FVector Start = PCM->GetActorTransform().GetLocation();
		const FVector End = Start + (PCM->GetActorTransform().GetRotation().GetForwardVector() * TraceLength);

		FHitResult TraceHitResult;
		FColor HitColor;
		bool HittingSomething;
		FVector HitCenter;
		if(GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECollisionChannel::ECC_Visibility))
		{
			if(FocusedActor != TraceHitResult.GetActor())
			{
				FocusedActor = TraceHitResult.GetActor();
				TraceInteractionArea(FocusedActor.GetClass() == AISInteractionArea::StaticClass());
			}
			HitColor = FColor::Green;
			HittingSomething = true;
			HitCenter = TraceHitResult.Location;
		}else
		{
			TraceInteractionArea(false);
			HitColor = FColor::Red;
			HittingSomething = false;
		}

		DrawDebugLine(GetWorld(), Start, End, HitColor, false, -1, 0, 2);
		if(HittingSomething)
		{
			DrawDebugBox(GetWorld(), HitCenter, FVector(2.f, 2.f, 2.f), FColor::Green, false,-1, 0, 5);
		}
	}
}

void UISACInteractionTrace::TraceInteractionArea(bool bTrace)
{
	
}

