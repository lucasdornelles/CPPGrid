// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CreditsPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API ACreditsPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

public:
	UFUNCTION()
	void ReturnToMenu();
	
	UFUNCTION()
	void ExitGame();
	
};
