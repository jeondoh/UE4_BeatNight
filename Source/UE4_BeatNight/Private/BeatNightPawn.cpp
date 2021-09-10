// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightPawn.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
ABeatNightPawn::ABeatNightPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitalizedData(); // 초기화
}

// Called when the game starts or when spawned
void ABeatNightPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeatNightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABeatNightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABeatNightPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Health -= DamageAmount;
	if(Health <= 0.f)
	{
		Health = 0.f;
		Die();

		auto EnemyController = Cast<AEnemyAIController>(EventInstigator);
		if(EnemyController)
		{
			// EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerDead"), true);			
		}
	}
	return DamageAmount;
}

void ABeatNightPawn::InitalizedData()
{
	MaxHealth = 1000.f;
	Health = 1000.f;
}

void ABeatNightPawn::Die()
{
}
