// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UPauseWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnToGameB;

	UFUNCTION()
	void CReturnToGame();
};
