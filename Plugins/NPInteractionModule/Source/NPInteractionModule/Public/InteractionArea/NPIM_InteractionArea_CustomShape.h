// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPIM_InteractionArea_Master.h"
#include "NPIM_InteractionArea_CustomShape.generated.h"

class UStaticMeshComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class NPINTERACTIONMODULE_API ANPIM_InteractionArea_CustomShape : public ANPIM_InteractionArea_Master
{
	GENERATED_BODY()

public:
	ANPIM_InteractionArea_CustomShape();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction Area|Components")
	TObjectPtr<UStaticMeshComponent> Shape;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction Area|Parameters")
	TObjectPtr<UStaticMesh> CustomShape;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction Area|Parameters")
	bool bDevMode;

private:
	TObjectPtr<UMaterialInterface> CustomShapeOutlineMaterialRef;
};
