// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelPortalActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelPortalActor::ALevelPortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	SceneRoot->InitSphereRadius(1.0f);
	RootComponent = SceneRoot;

	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrameMesh"));
	FrameMesh->SetupAttachment(RootComponent);

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALevelPortalActor::BeginPlay()
{
	Super::BeginPlay();

	PortalMesh->OnComponentBeginOverlap.AddDynamic(this, &ALevelPortalActor::OnPortalOverlapBegin);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);
		CurveTimeline.SetPlayRate(1.0f);

		StartLocation = EndLocation = GetActorLocation();
		EndLocation.Z += ZOffset;
	}

	IsPortalActive = false;
	
}

// Called every frame
void ALevelPortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}

void ALevelPortalActor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

void ALevelPortalActor::AnimatePortal()
{
	CurveTimeline.PlayFromStart();
	IsPortalActive = true;
}

void ALevelPortalActor::OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (IsPortalActive)
	{
		PortalOverlapEvent.Broadcast();
	}
}
