// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ISInteractionArea.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class THESURVIVALIST_API AISInteractionArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AISInteractionArea();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="InteractionArea", meta=(AllowPrivateAccess=True))
	TObjectPtr<USceneComponent> ActorRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="InteractionArea", meta=(AllowPrivateAccess=True))
	TObjectPtr<UBoxComponent> Box;

	bool bFocused;

public:	
	UFUNCTION(BlueprintCallable, Category="InteractionArea")
	void ToggleFocus(bool NewFocused);
};
