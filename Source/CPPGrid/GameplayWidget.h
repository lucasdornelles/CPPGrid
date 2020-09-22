// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"

#include "GameplayWidget.generated.h"

/**
 * Gameplay HUD
 */
UCLASS()
class CPPGRID_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UGameplayWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBarLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBarRight;
	
	UFUNCTION()
	void UpdateHealthText(int32 NewValue);

	UFUNCTION()
	void InitializeTotalHealth(int32 Value);

private:

	float TotalHealth;
	
};
