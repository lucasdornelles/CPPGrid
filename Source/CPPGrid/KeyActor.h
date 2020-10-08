// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "InteractableActorInterface.h"
#include "KeyActor.generated.h"

UCLASS()
class CPPGRID_API AKeyActor : public AActor, public IInteractableActorInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* KeyOuterMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* KeyMidleMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* KeyInnerMesh;

	UPROPERTY(EditAnywhere, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	EInteractableType InteractableType;
	
public:	
	// Sets default values for this actor's properties
	AKeyActor();

	UFUNCTION()
	void TimelineProgress(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	//Curve to control floating movement
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EInteractableType Interact() override;

};
