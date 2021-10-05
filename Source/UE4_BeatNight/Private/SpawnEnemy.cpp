// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnEnemy.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(TagName);
}

void ASpawnEnemy::SpawnEnemy()
{
	FActorSpawnParameters Param;
	// AdjustIfPossibleButAlwaysSpawn
	// 엑터 충돌시 근처 충돌하지 않는 위치에 스폰,
	// 찾지 못하면 AlwaysSpawn으로 동작
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEnemy* CastEnemy = GetWorld()->SpawnActor<AEnemy>(SpawnEnemyType, GetActorLocation(), GetActorRotation(), Param);

	// Enemy 몬스터명 & 정찰 포인트 지정
	if(CastEnemy)
	{
		CastEnemy->SetMonsterName(SpawnMonsterName); // 스테이지 구별을 위해 몬스터명 지정
		CastEnemy->SetMonsterTagName(SpawnMonsterTagName); // 스테이지 구별을 위해 몬스터명 지정
		CastEnemy->SetPatrolPoint(PatrolPoint); // 정찰 포인트1
		CastEnemy->SetPatrolPoint2(PatrolPoint2); // 정찰 포인트2
		// Enemy의 BehaviorTree설정 (AI 동작)
		CastEnemy->SetEnemyAIController();
	}
}
