// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ISACInteractionTrace.generated.h"


UCLASS(Blueprintable,meta=(BlueprintSpawnableComponent))
class THESURVIVALIST_API UISACInteractionTrace : public UActorComponent
{
	GENERATED_BODY()

public:
	UISACInteractionTrace();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InteractionTrace")
	float TraceLength;

private:
	TObjectPtr<AActor> FocusedActor;
	
	void Trace(float DeltaTime);
	void TraceInteractionArea(bool bTrace);
};
