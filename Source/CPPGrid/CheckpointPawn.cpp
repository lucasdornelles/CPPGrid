// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointPawn.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACheckpointPawn::ACheckpointPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SceneRoot"));
	SceneRoot->InitCapsuleSize(55.f, 96.0f);
	RootComponent = SceneRoot;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpointPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACheckpointPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

