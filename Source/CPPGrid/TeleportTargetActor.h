// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportTargetActor.generated.h"

UCLASS()
class CPPGRID_API ATeleportTargetActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UArrowComponent* ArrowComponent;
	
public:	
	// Sets default values for this actor's properties
	ATeleportTargetActor();

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	int32 TargetIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
