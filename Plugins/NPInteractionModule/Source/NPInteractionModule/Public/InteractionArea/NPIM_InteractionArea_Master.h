// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPIM_InteractionArea_Master.generated.h"

class UShapeComponent;
class UWidgetComponent;

UCLASS(Abstract)
class NPINTERACTIONMODULE_API ANPIM_InteractionArea_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPIM_InteractionArea_Master();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Interaction Area|Components")
	TObjectPtr<USceneComponent> ActorRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Area|Parameters")
	float InteractDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction Area|Parameters")
	bool bDirectionDetect;

	bool bFocused;

private:
	FName DirectionDetectShapeTag;
	FName InteractionWidgetCompTag;
	TObjectPtr<UShapeComponent> DirectionShapeRef;
	TObjectPtr<UWidgetComponent> InteractionWidgetRef;

	UFUNCTION()
	void OnDirectionShapeOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnDirectionShapeOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	UFUNCTION(BlueprintCallable, Category="Interaction Area")
	virtual void ToggleFocus(bool NewFocused);

	UFUNCTION(BlueprintPure, Category="Interaction Area")
	FORCEINLINE float GetInteractDuration() const { return InteractDuration; }

	UFUNCTION(BlueprintPure, Category="Interaction Area")
	FORCEINLINE UWidgetComponent* GetInteractionWidgetRef() const { return InteractionWidgetRef; }

	bool CanFocus(const AActor* ActorToCheckOverlap) const;
};
