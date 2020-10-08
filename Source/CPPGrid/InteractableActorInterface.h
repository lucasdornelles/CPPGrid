// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableActorInterface.generated.h"

UENUM(BlueprintType)
enum class EInteractableType : uint8 {
	NONE UMETA(DisplayName = "None"),
	BLUEKEY UMETA(DisplayName = "BlueKey"),
	GREENKEY UMETA(DisplayName = "GreenKey"),
	PINKKEY UMETA(DisplayName = "PinkKey"),
	BLUETOTEM UMETA(DisplayName = "BlueTotem"),
	GREENTOTEM UMETA(DisplayName = "GreenTotem"),
	PINKTOTEM UMETA(DisplayName = "PinkTotem")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Implement interface for actor to be interacted by player
 */
class CPPGRID_API IInteractableActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EInteractableType Interact();
};
