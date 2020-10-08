// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Components/WidgetComponent.h"
#include "DeathWidget.h"
#include "PauseWidget.h"

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

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<UUserWidget> DeathWidgetClass;

	void UpdateHealthText(int32 NewValue);

	void InitializeTotalHealth(int32 Value);

	UFUNCTION()
	bool SwitchGamePause();

	UFUNCTION()
	void ShowDeathMenu();

	UFUNCTION()
	void ShowGameplayMenu();

	UFUNCTION()
	UPauseWidget* GetPauseWidget();

	UFUNCTION()
	UDeathWidget* GetDeathWidget();

	void SetBlueKey(bool Held);
	void SetGreenKey(bool Held);
	void SetPinkKey(bool Held);

private:

	// Generatad Widgets pointers sems to become invalidated after some time if not decorated with UPROPERTY()

	UPROPERTY()
	class UGameplayWidget* GameplayWidget;

	UPROPERTY()
	class UPauseWidget* PauseWidget;

	UPROPERTY()
	class UDeathWidget* DeathWidget;

	bool IsPaused;

	
};
