// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TeleportTargetActor.h"

// Sets default values
APortalActor::APortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	SceneRoot->InitSphereRadius(1.0f);
	RootComponent = SceneRoot;

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetupAttachment(RootComponent);

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	PortalMesh->SetupAttachment(RootComponent);
	

}

// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();

	PortalMesh->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnPortalOverlapBegin);

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindUFunction(this, FName("TimelineProgress"));
		CurveTimeline.AddInterpFloat(CurveFloat, TimelineProgress);
		CurveTimeline.SetLooping(false);
		CurveTimeline.SetPlayRate(1.0f);

		FOnTimelineEvent FinishFunc = FOnTimelineEvent();
		FinishFunc.BindUFunction(this, FName("ReturnToStartLocation"));

		CurveTimeline.SetTimelineFinishedFunc(FinishFunc);

		StartLocation = EndLocation = PortalMesh->GetRelativeLocation();
		EndLocation.Z += ZOffset;

		UWorld* World = GetWorld();
		if (World)
		{
			World->GetTimerManager().SetTimer(PortalAnimationTrigger, this, &APortalActor::FireAnimation, RepeatTimer, true);

		}
	}
	
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveTimeline.TickTimeline(DeltaTime);

}

void APortalActor::TimelineProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	PortalMesh->SetRelativeLocation(NewLocation);
	
}

void APortalActor::FireAnimation()
{
	if (CurveFloat)
	{
		CurveTimeline.PlayFromStart();
	}
}

void APortalActor::ReturnToStartLocation()
{
	PortalMesh->SetRelativeLocation(StartLocation);
}

void APortalActor::OnPortalOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Overlap!"));
	
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, ATeleportTargetActor::StaticClass(), OutActors);

	FVector TargetLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator TargetRotation = FRotator(0.0f, 0.0f, 0.0f);
	bool bTargetFound = false;
	for (AActor* Actor : OutActors)
	{
		ATeleportTargetActor* Target = Cast<ATeleportTargetActor>(Actor);
		if (Target)
		{
			if (TargetIndex == Target->TargetIndex)
			{
				bTargetFound = true;
				TargetLocation = Target->GetActorLocation();
				TargetRotation = Target->GetActorRotation();
			}
		}
	}

	if (bTargetFound)
	{
		OtherActor->SetActorLocation(TargetLocation);
		Cast<ACharacter>(OtherActor)->GetController()->SetControlRotation(TargetRotation);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Target Not Found."));
	}
	
}

