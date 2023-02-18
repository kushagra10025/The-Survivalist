// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionArea/NPIM_InteractionArea_CustomShape.h"

#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ANPIM_InteractionArea_CustomShape::ANPIM_InteractionArea_CustomShape()
{
	Shape = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shape"));
	Shape->SetupAttachment(RootComponent);
	Shape->SetRelativeScale3D(FVector(1.05f, 1.05f, 1.05f));
	Shape->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Shape->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	Shape->SetHiddenInGame(true);

	const ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef = ConstructorHelpers::FObjectFinder<UMaterialInterface>(TEXT("/Script/Engine.Material'/NPInteractionModule/Materials/M_CustomShapeOutline.M_CustomShapeOutline'"));

	if(MaterialRef.Object)
	{
		CustomShapeOutlineMaterialRef = MaterialRef.Object;
	}
}

#if WITH_EDITOR
void ANPIM_InteractionArea_CustomShape::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.Property)
	{
		if(CustomShape && CustomShapeOutlineMaterialRef)
		{
			Shape->SetStaticMesh(CustomShape);
			if(bDevMode)
			{
				Shape->SetVisibility(true);
				for(const FName& MaterialSlotName : Shape->GetMaterialSlotNames())
				{
					Shape->SetMaterialByName(MaterialSlotName, CustomShapeOutlineMaterialRef);
				}
			}else
			{
				Shape->SetVisibility(false);
			}
		}
	}
}
#endif
