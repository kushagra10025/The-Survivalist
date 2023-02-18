// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TSBaseCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UISACInteractionTrace;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Contexts")
	TObjectPtr<UInputMappingContext> PlayerMovementMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Actions")
	TObjectPtr<UInputAction> MoveForwardsAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Actions")
	TObjectPtr<UInputAction> MoveSidewaysAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Actions")
	TObjectPtr<UInputAction> TurnRightAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Actions")
	TObjectPtr<UInputAction> LookUpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BaseCharacter|EnhancedInput|Actions")
	TObjectPtr<UInputAction> JumpAction;

	void MoveForwards(const FInputActionValue& Value);
	void MoveSideways(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void TurnRight(const FInputActionValue& Value);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BaseCharacter|Camera", meta=(AllowPrivateAccess=True))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

public:	
	
};
