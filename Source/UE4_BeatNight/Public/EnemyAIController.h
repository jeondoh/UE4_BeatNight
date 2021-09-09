// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(BlueprintReadWrite, Category="AI|Behavior", meta=(AllowPrivateAccess=true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite, Category="AI|Behavior", meta=(AllowPrivateAccess=true))
	class UBehaviorTreeComponent* BehaviorTreeComponent;
	
// Getter & Setter	
public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const {return BlackboardComponent;}
	
	
};
