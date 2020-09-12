// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "EnemyActor.generated.h"

UCLASS()
class CPPGRID_API AEnemyActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* EnemyMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USphereComponent* SceneRoot;
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

	//Floating motion timeline function
	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	//Curve to control floating movement
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
