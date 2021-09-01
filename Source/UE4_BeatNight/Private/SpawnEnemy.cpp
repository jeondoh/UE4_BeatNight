// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnEnemy.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnEnemy::ASpawnEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnDelayTime = 1.0f; // 스폰 딜레이 시간
	Enemy = CreateDefaultSubobject<AEnemy>(TEXT("Enemy"));
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

	// 스테이지 몬스터 존재 확인(추후 스테이지 작업시 사용)
	/*
	TArray<AActor*> arrOutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), arrOutActors);

	if(arrOutActors.IsValidIndex(0))
	{
		for(int i = 0; i < arrOutActors.Num(); ++i)
		{
			AEnemy* FindEnemy = dynamic_cast<AEnemy*>(arrOutActors[i]);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FindEnemy->GetMonsterName());
		}	
	}
	*/
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

	// 스폰시 몬스터명 지정(스테이지 구별을 위해 필요)
	// AEnemy* Enemy = Cast<AEnemy>(SpawnEnemyType);
	if(Enemy)
	{
		Enemy->SetMonsterName(SpawnMonsterName);
	}

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
}
