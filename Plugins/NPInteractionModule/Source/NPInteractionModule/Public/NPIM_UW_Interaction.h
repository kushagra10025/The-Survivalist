// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPIM_UW_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class NPINTERACTIONMODULE_API UNPIM_UW_Interaction : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction Widget")
	bool bTimedInteraction; // USE THIS LATER

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction Widget")
	void SetTimerBarPercent(float Percent);
	
};
