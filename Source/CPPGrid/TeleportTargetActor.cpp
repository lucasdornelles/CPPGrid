// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportTargetActor.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATeleportTargetActor::ATeleportTargetActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATeleportTargetActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

