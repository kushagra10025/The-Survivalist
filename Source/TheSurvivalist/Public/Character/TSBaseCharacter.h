// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TSBaseCharacter.generated.h"

class UInputMappingContext;
class UCameraComponent;

UCLASS()
class THESURVIVALIST_API ATSBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATSBaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput")
	TObjectPtr<UInputMappingContext> PlayerMovementMappingContext;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

private:

public:	
	
};
