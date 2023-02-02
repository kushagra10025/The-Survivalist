// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPIM_AC_InteractionTrace.generated.h"

class ANPIM_InteractionArea_Master;
class UNPIM_UW_Interaction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NPINTERACTIONMODULE_API UNPIM_AC_InteractionTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNPIM_AC_InteractionTrace();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Trace")
	float TraceLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Trace")
	float UpdateInteractionInterval;

private:
	bool bTracingInteractionArea;
	TObjectPtr<ANPIM_InteractionArea_Master> FocusedInteractionArea;
	TObjectPtr<AActor> FocusedActor;
	float InteractDuration;
	TWeakObjectPtr<UNPIM_UW_Interaction> CurrentInteractionWidgetRef;
	FTimerHandle TH_TimedInteraction;
	float InteractionProgress;

	void Trace();
	void TraceInteractionArea(bool bTrace);
	void PerformInteract(const ANPIM_InteractionArea_Master* InteractionArea); // Try to Execute on Server for Multiplayer Ready
	UFUNCTION()
	void UpdateInteractionProgress();
	void StopInteraction();
	void RunEventAfterInteraction();

public:
	UFUNCTION(BlueprintCallable, Category="Interaction Trace")
	void SetupInteractionTrace();
	UFUNCTION(BlueprintCallable, Category="Interaction Trace")
	void TryToInteract(bool bIn);

	void ResetTrace();
		
};
