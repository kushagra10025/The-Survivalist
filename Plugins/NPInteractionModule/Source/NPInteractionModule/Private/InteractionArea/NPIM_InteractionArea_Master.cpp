// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionArea/NPIM_InteractionArea_Master.h"

#include "NPIM_AC_InteractionTrace.h"
#include "NPIM_InteractionInterface.h"
#include "Components/ShapeComponent.h"
#include "Components/WidgetComponent.h"

ANPIM_InteractionArea_Master::ANPIM_InteractionArea_Master():
	DirectionDetectShapeTag("direction_interact"),
	InteractionWidgetCompTag("widget_interact")
{
	PrimaryActorTick.bCanEverTick = true;

	ActorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ActorRoot"));
	SetRootComponent(ActorRoot);

}

void ANPIM_InteractionArea_Master::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPIM_InteractionArea_Master::BeginPlay()
{
	Super::BeginPlay();

	if(GetParentActor())
	{
		if(!GetParentActor()->GetComponentsByTag(UShapeComponent::StaticClass(), DirectionDetectShapeTag).IsEmpty())
		{
			DirectionShapeRef = Cast<UShapeComponent>(GetParentActor()->GetComponentsByTag(UShapeComponent::StaticClass(), DirectionDetectShapeTag)[0]);
			DirectionShapeRef->OnComponentBeginOverlap.AddDynamic(this, &ANPIM_InteractionArea_Master::OnDirectionShapeOverlapBegin);
			DirectionShapeRef->OnComponentEndOverlap.AddDynamic(this, &ANPIM_InteractionArea_Master::OnDirectionShapeOverlapEnd);
		}

		if(!GetParentActor()->GetComponentsByTag(UWidgetComponent::StaticClass(), InteractionWidgetCompTag).IsEmpty())
		{
			InteractionWidgetRef = Cast<UWidgetComponent>(GetParentActor()->GetComponentsByTag(UWidgetComponent::StaticClass(), InteractionWidgetCompTag)[0]);	
		}
	}
}

bool ANPIM_InteractionArea_Master::CanFocus(const AActor* ActorToCheckOverlap) const
{
	if(bDirectionDetect)
	{
		return DirectionShapeRef->IsOverlappingActor(ActorToCheckOverlap);
	}
	return true;
}

void ANPIM_InteractionArea_Master::OnDirectionShapeOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(UNPIM_AC_InteractionTrace* InteractionTraceComp = Cast<UNPIM_AC_InteractionTrace>(OtherActor->GetComponentByClass(UNPIM_AC_InteractionTrace::StaticClass())))
	{
		InteractionTraceComp->ResetTrace();
	}
}

void ANPIM_InteractionArea_Master::OnDirectionShapeOverlapEnd(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UNPIM_AC_InteractionTrace* InteractionTraceComp = Cast<UNPIM_AC_InteractionTrace>(OtherActor->GetComponentByClass(UNPIM_AC_InteractionTrace::StaticClass())))
	{
		InteractionTraceComp->ResetTrace();
	}
}

void ANPIM_InteractionArea_Master::ToggleFocus(bool NewFocused)
{
	bFocused = NewFocused;
	if(GetParentActor())
	{
		if(GetParentActor()->GetClass()->ImplementsInterface(UNPIM_InteractionInterface::StaticClass()))
		{
			INPIM_InteractionInterface::Execute_Interface_ToggleFocus(GetParentActor(), bFocused);
			if(InteractionWidgetRef)
			{
				InteractionWidgetRef->SetHiddenInGame(!bFocused);	
			}
		}
	}
}
