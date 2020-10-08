// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AKeyActor::AKeyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));

	RootComponent = SceneRoot;

	KeyOuterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OuterMesh"));
	KeyMidleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MidleMesh"));
	KeyInnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InnerMesh"));

	KeyOuterMesh->SetupAttachment(RootComponent);
	KeyMidleMesh->SetupAttachment(RootComponent);
	KeyInnerMesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AKeyActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(true);
		CurveTimeline.SetPlayRate(1.0f);

		CurveTimeline.PlayFromStart();
	}

}

// Called every frame
void AKeyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}

void AKeyActor::TimelineProgress(float Value)
{
	FRotator OuterRotator = FRotator(Value, 0.0f, 0.0f);
	FRotator MidleRotator = FRotator(0.0f, Value, 0.0f);
	FRotator InnerRotator = FRotator(0.0f, 0.0f, Value);

	KeyOuterMesh->SetWorldRotation(OuterRotator);
	KeyMidleMesh->SetWorldRotation(MidleRotator);
	KeyInnerMesh->SetWorldRotation(InnerRotator);
}

EInteractableType AKeyActor::Interact()
{
	Destroy();
	return InteractableType;
	
}