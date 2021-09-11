// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"

#include "Enemy.h"
#include "BeatNightPawn.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBullet::AEnemyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
	// StaticMeshComponent->SetupAttachment(GetRootComponent());

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(GetRootComponent());
	
	BulletSpeed = 1800.f; // 총알속도
	CanMove = false;
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::BoxCompBeginOverlap);

	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABeatNightPawn::StaticClass());
	ABeatNightPawn* Player = Cast<ABeatNightPawn>(FindActor);
	if(Player)
	{
		FVector NewLocation = Player->GetActorLocation() - GetActorLocation();
		NewLocation.Normalize();
		Direction = NewLocation;
	}
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 총알 Player에게
	if(CanMove)
	{
		FVector Location = Direction * BulletSpeed;
		SetActorLocation(GetActorLocation() + Location * DeltaTime);
	}

}

void AEnemyBullet::SetBulletInfos(AEnemy* GetEnemy, float Speed)
{
	BulletSpeed = Speed;
	Enemy = GetEnemy;
	CanMove = true;
}

void AEnemyBullet::BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPawn* TargetPlayer = Cast<ABeatNightPawn>(OtherActor);
	// 총 맞는 대상이 Player
	if(TargetPlayer)
	{
		// 총 맞는 위치에 파티클 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BulletParticles, GetActorTransform()); 
		// Player에게 데미지 입힘
		if(Enemy)
		{
			Enemy->DoDamage(TargetPlayer);
		}
		// 총알 제거
		Destroy();
	}
	// Destroy();
}

