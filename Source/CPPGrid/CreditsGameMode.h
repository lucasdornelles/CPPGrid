// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "CreditsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API ACreditsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	void ChangeLevel();


	void ExitGame();

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> CreditsWidgetClass;

private:

	class UUserWidget* CreditsWidget;
	
};
