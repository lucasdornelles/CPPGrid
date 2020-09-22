// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class CPPGRID_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

	// The Behavior tree component
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorComp;

	// The Blackboard Component
	UPROPERTY()
	UBlackboardComponent* BlackboardComp;
	
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey; // reference to the players location

	virtual void OnPossess(APawn* EPawn) override;

public:
	AEnemyAIController();

	// To be called py AI pawn on sensing event
	void SetPlayerCaught(APawn* PlayerPawn);

	// inline getter | get the AI's blackboard
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }
};
