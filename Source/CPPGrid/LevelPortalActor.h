// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "LevelPortalActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPortalOverlap);

UCLASS()
class CPPGRID_API ALevelPortalActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USphereComponent* SceneRoot;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* FrameMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	UStaticMeshComponent* PortalMesh;
	
public:	
	// Sets default values for this actor's properties
	ALevelPortalActor();

	UFUNCTION()
	void TimelineProgress(float Value);

	UFUNCTION()
	void AnimatePortal();

	UPROPERTY()
	bool IsPortalActive;

	FOnPortalOverlap PortalOverlapEvent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float ZOffset;

	UPROPERTY()
	FVector StartLocation;

	UPROPERTY()
	FVector EndLocation;

	UFUNCTION()
	void OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
