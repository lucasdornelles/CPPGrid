// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"

#include "GameplayHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AGameplayHUD : public AHUD
{
	GENERATED_BODY()

public:

	AGameplayHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> GameplayWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	void UpdateHealthText(int32 NewValue);

	void InitializeTotalHealth(int32 Value);

	bool SwitchGamePause();

private:

	// Generatad Widgets pointers sems to become invalidated after some time if not decorated with UPROPERTY()

	UPROPERTY()
	class UGameplayWidget* GameplayWidget;

	UPROPERTY()
	class UPauseWidget* PauseWidget;

	bool IsPaused;

	
};
