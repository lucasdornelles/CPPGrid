// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MovableBlockActor.generated.h"

UCLASS()
class CPPGRID_API AMovableBlockActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* BlockMesh;
	
public:	
	// Sets default values for this actor's properties
	AMovableBlockActor();

	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	//Curve to control Floating movement
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float XOffset;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float YOffset;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
