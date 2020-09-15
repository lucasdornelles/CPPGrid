// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyPawn.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AEnemyAIController::AEnemyAIController()
{
	// Initialise the blackboard and behavior tree
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	// Initialise the blackboard keys
	// name of the key in the blackboard
	PlayerKey = "Target";
}

void AEnemyAIController::OnPossess(APawn* EPawn)
{
	Super::OnPossess(EPawn);

	// Get Reference to the AI Pawn
	AEnemyPawn* EnemyPawn = Cast<AEnemyPawn>(EPawn);

	// Initialize Blackboard and Behavior tree
	if (EnemyPawn)
	{
		if (EnemyPawn->BehaviourTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*EnemyPawn->BehaviourTree->BlackboardAsset);
		}

		BehaviorComp->StartTree(*EnemyPawn->BehaviourTree);
	}

}

void AEnemyAIController::SetPlayerCaught(APawn* PlayerPawn)
{
	if (BlackboardComp)
	{
		// Set Player object on blackboart to be used by the behavior tree
		BlackboardComp->SetValueAsObject(PlayerKey, PlayerPawn);
	}
}
