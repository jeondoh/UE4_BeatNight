// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightPlayer.h"

#include "EnemyAIController.h"

// Sets default values
ABeatNightPlayer::ABeatNightPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitalizedData(); // 초기화
}

// Called when the game starts or when spawned
void ABeatNightPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeatNightPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABeatNightPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABeatNightPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	DamageAmount = Defense >= DamageAmount ? 0 : DamageAmount - Defense;
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

void ABeatNightPlayer::InitalizedData()
{
	MaxHealth = 1000.f;
	Health = 1000.f;
}

void ABeatNightPlayer::Die()
{
	
}
