// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Item.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 변수 초기화
	InitalizedData();

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	
	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::InitalizedData()
{
	MaxHealth = 100.f; // 최대 체력
	Health = 100.f; // 체력
	EnemyDamage = 10.f; // 데미지
	MonsterName = TEXT(""); // 몬스터명
}

void AEnemy::DropItem()
{
	if(bDropItem && ItemType)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// Enemy 위치에 스폰
		const FVector EnemyLocate = GetActorLocation();
		// 아이템 스폰
		GetWorld()->SpawnActor<AItem>(ItemType, EnemyLocate, GetActorRotation(), Param);
		// 아이템 드롭 사운드
		if(DropSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DropSound, EnemyLocate);
		}
	}
	
}

