// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractableActorInterface.h"
#include "TotemActor.generated.h"

UCLASS()
class CPPGRID_API ATotemActor : public AActor, public IInteractableActorInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UBoxComponent* HitBox;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* TotemBaseMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* RingMesh;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	EInteractableType InteractableType;

	UPROPERTY(EditAnywhere, Category = Key, meta = (AllowPrivateAcess = "true"))
	TSubclassOf<class AKeyActor> SpawnInfoKeyActor;

	
public:	
	// Sets default values for this actor's properties
	ATotemActor();

	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	//Curve to control ring movement
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EInteractableType Interact() override;

	void ActivateTotem();

};
