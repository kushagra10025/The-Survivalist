// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TSBaseCharacter.generated.h"

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

private:

public:	
	
};
