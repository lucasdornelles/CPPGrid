// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayGameMode.h"
#include "FirstLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AFirstLevelGameMode : public AGameplayGameMode
{
	GENERATED_BODY()
	

public:

	virtual void BeginPlay() override;

private:

	bool IsHoldingBlueKey;
	bool IsActiveBlueTotem;

	bool IsHoldingGreenKey;
	bool IsActiveGreenTotem;

	bool IsHoldingPinkKey;
	bool IsActivePinkTotem;

public:

	virtual void ResolveInteract(EInteractableType InteractType) override;

	virtual void ChangeLevel() override;
};
