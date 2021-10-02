// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnSpiderEnemy.h"

#include "BeatNightPlayer.h"
#include "Enemy.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnSpiderEnemy::ASpawnSpiderEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnSpiderEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnSpiderEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnSpiderEnemy::SpawnEnemy()
{
	ABeatNightPlayer* FindPlayer = Cast<ABeatNightPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ABeatNightPlayer::StaticClass()));
	FActorSpawnParameters Param;
	// AdjustIfPossibleButAlwaysSpawn
	// 엑터 충돌시 근처 충돌하지 않는 위치에 스폰,
	// 찾지 못하면 AlwaysSpawn으로 동작
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* CastEnemy = GetWorld()->SpawnActor<AEnemy>(SpawnEnemyType, GetActorLocation(), GetActorRotation(), Param);
	if(CastEnemy)
	{
		CastEnemy->SetMonsterName(SpawnMonsterName); // 스테이지 구별을 위해 몬스터명 지정
		CastEnemy->SetEnemyAIController(); // Enemy의 BehaviorTree설정 (AI 동작)
		// 소환된 거미가 바로 캐릭터에게 이동(공격)할 수 있도록
		if(CastEnemy->GetEnemyController())
		{
			CastEnemy->GetEnemyController()->GetBlackboardComponent()->SetValueAsObject(FName("Target"), FindPlayer);
		}
	}
}
