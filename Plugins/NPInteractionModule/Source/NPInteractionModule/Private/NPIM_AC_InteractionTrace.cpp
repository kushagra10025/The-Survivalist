// Fill out your copyright notice in the Description page of Project Settings.


#include "NPIM_AC_InteractionTrace.h"

#include "NPIM_InteractionInterface.h"
#include "NPIM_UW_Interaction.h"
#include "TimerManager.h"
#include "Components/WidgetComponent.h"
#include "InteractionArea/NPIM_InteractionArea_Master.h"
#include "Kismet/GameplayStatics.h"

UNPIM_AC_InteractionTrace::UNPIM_AC_InteractionTrace():
	TraceLength(400.f),
	UpdateInteractionInterval(0.01f)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetComponentTickInterval(0.03f);

}

void UNPIM_AC_InteractionTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Trace();
}

void UNPIM_AC_InteractionTrace::BeginPlay()
{
	Super::BeginPlay();

}

void UNPIM_AC_InteractionTrace::Trace()
{
	if(const APlayerCameraManager* PCM = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		const FVector Start = PCM->GetActorTransform().GetLocation();
		const FVector End = Start + (PCM->GetActorTransform().GetRotation().GetForwardVector() * TraceLength);

		FHitResult TraceHitResult;
		if(GetWorld()->LineTraceSingleByChannel(TraceHitResult, Start, End, ECollisionChannel::ECC_Visibility))
		{
			if(FocusedActor != TraceHitResult.GetActor())
			{
				FocusedActor = TraceHitResult.GetActor();
				TraceInteractionArea(FocusedActor.IsA(ANPIM_InteractionArea_Master::StaticClass()));
			}
		}else
		{
			TraceInteractionArea(false);
		}
	}
}

void UNPIM_AC_InteractionTrace::TraceInteractionArea(bool bTrace)
{
	if(bTrace)
	{
		if(bTracingInteractionArea)
		{
			FocusedInteractionArea->ToggleFocus(false);
		}
		FocusedInteractionArea = Cast<ANPIM_InteractionArea_Master>(FocusedActor);
		if(FocusedInteractionArea)
		{
			if(FocusedInteractionArea->CanFocus(GetOwner()))
			{
				FocusedInteractionArea->ToggleFocus(true);
				bTracingInteractionArea = true;	
			}else
			{
				// Same as Line 87
				if(bTracingInteractionArea)
				{
					bTracingInteractionArea = false;
					FocusedInteractionArea->ToggleFocus(false);
					FocusedActor = nullptr;
					FocusedInteractionArea = nullptr;
					StopInteraction();
				}
			}
		}
	}else
	{
		if(bTracingInteractionArea)
		{
			bTracingInteractionArea = false;
			FocusedInteractionArea->ToggleFocus(false);
			FocusedActor = nullptr;
			FocusedInteractionArea = nullptr;
			StopInteraction();
		}
	}
}

void UNPIM_AC_InteractionTrace::PerformInteract(const ANPIM_InteractionArea_Master* InteractionArea)
{
	if(AActor* IAPA = InteractionArea->GetParentActor())
	{
		if(IAPA->GetClass()->ImplementsInterface(UNPIM_InteractionInterface::StaticClass()))
		{
			INPIM_InteractionInterface::Execute_Interface_Interact(IAPA);
		}
	}
}

void UNPIM_AC_InteractionTrace::UpdateInteractionProgress()
{
	InteractionProgress += ((1.0f / InteractDuration) * UpdateInteractionInterval);
	CurrentInteractionWidgetRef->SetTimerBarPercent(InteractionProgress);
	if(InteractionProgress >= 1.0f)
	{
		StopInteraction();
		PerformInteract(FocusedInteractionArea);
		RunEventAfterInteraction();
	}
}

void UNPIM_AC_InteractionTrace::StopInteraction()
{
	if(InteractionProgress > 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TH_TimedInteraction);
		CurrentInteractionWidgetRef->SetTimerBarPercent(0.f);
		InteractionProgress = 0.f;
		CurrentInteractionWidgetRef = nullptr;
	}
}

void UNPIM_AC_InteractionTrace::RunEventAfterInteraction()
{
	if(const AActor* FIAPA = FocusedInteractionArea->GetParentActor())
	{
		// TODO Run Event After Interaction
	}
}

void UNPIM_AC_InteractionTrace::ResetTrace()
{
	FocusedActor = nullptr;
}

void UNPIM_AC_InteractionTrace::SetupInteractionTrace()
{
	if(const APawn* PawnOwner = Cast<APawn>(GetOwner()))
	{
		if(PawnOwner->IsLocallyControlled())
		{
			SetComponentTickEnabled(true);
		}
	}
}

void UNPIM_AC_InteractionTrace::TryToInteract(bool bIn)
{
	if(bIn)
	{
		if(bTracingInteractionArea)
		{
			InteractDuration = FocusedInteractionArea->GetInteractDuration();
			if(InteractDuration > 0.f)
			{
				// Hold to Interact
				if(AActor* FIAPA = FocusedInteractionArea->GetParentActor())
				{
					if(const UWidgetComponent* WidgetCompRef = FocusedInteractionArea->GetInteractionWidgetRef())
					{
						CurrentInteractionWidgetRef = Cast<UNPIM_UW_Interaction>(WidgetCompRef->GetWidget());
						if(CurrentInteractionWidgetRef.IsValid())
						{
							FTimerDelegate Delegate;
							Delegate.BindUFunction(this, "UpdateInteractionProgress");
							GetWorld()->GetTimerManager().SetTimer(TH_TimedInteraction, Delegate, UpdateInteractionInterval, true);
						}
					}
				}
			}else
			{
				// Instant Interact
				PerformInteract(FocusedInteractionArea);
				RunEventAfterInteraction();
			}
		}
	}else
	{
		StopInteraction();
	}
}

