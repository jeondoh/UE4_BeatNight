// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnEnemy.h"
#include "Enemy.h"

// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnDelayTime = 1.0f; // 스폰 딜레이 시간
}

// Called when the game starts or when spawned
void ASpawnEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemyToDelay(); // Enemy 스폰
}

// Called every frame
void ASpawnEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnEnemy::SpawnEnemyToDelay()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnEnemy::SpawnEnemy, SpawnDelayTime);
}

void ASpawnEnemy::SpawnEnemy()
{
	FActorSpawnParameters Param;
	// AdjustIfPossibleButAlwaysSpawn
	// 엑터 충돌시 근처 충돌하지 않는 위치에 스폰,
	// 찾지 못하면 AlwaysSpawn으로 동작
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const FVector Locate = GetActorLocation();
	GetWorld()->SpawnActor<AEnemy>(SpawnEnemyType, Locate, GetActorRotation(), Param);
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);	
}
