// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnContinue);

/**
 * 
 */
UCLASS()
class CPPGRID_API UDeathWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UDeathWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ContinueB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* MainMenuB;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ExitGameB;

	UFUNCTION()
	void CContinue();

	UFUNCTION()
	void CMainMenu();

	UFUNCTION()
	void CExitGame();

	FOnContinue OnContinue;

};
