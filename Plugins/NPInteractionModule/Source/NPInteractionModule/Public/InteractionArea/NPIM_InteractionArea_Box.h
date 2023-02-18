// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPIM_InteractionArea_Master.h"
#include "NPIM_InteractionArea_Box.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS(Blueprintable)
class NPINTERACTIONMODULE_API ANPIM_InteractionArea_Box : public ANPIM_InteractionArea_Master
{
	GENERATED_BODY()

public:
	ANPIM_InteractionArea_Box();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction Area|Components")
	TObjectPtr<UBoxComponent> Box;
	
};
