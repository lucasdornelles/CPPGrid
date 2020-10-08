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

	UPROPERTY(EditAnywhere, Category = Texture, meta = (AllowPrivateAcess = "true"))
	class UTexture2D* TWhiteKey;

	UPROPERTY(EditAnywhere, Category = Texture, meta = (AllowPrivateAcess = "true"))
	UTexture2D* TBlueKey;

	UPROPERTY(EditAnywhere, Category = Texture, meta = (AllowPrivateAcess = "true"))
	UTexture2D* TGreenKey;

	UPROPERTY(EditAnywhere, Category = Texture, meta = (AllowPrivateAcess = "true"))
	UTexture2D* TPinkKey;

public:

	UGameplayWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UProgressBar* HealthBarLeft;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBarRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* KeyBlue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* KeyGreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* KeyPink;
	
	UFUNCTION()
	void UpdateHealthText(int32 NewValue);

	UFUNCTION()
	void InitializeTotalHealth(int32 Value);

	UFUNCTION()
	void SetBlueKey(bool Held);

	UFUNCTION()
	void SetGreenKey(bool Held);

	UFUNCTION()
	void SetPinkKey(bool Held);

private:

	float TotalHealth;
	
};
