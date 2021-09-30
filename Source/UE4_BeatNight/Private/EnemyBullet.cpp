// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"

#include "Enemy.h"
#include "BeatNightPlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

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

	BulletTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletParticle"));
	BulletTrail->SetupAttachment(GetRootComponent());
	
	BulletSpeed = 1800.f; // 총알속도
	CanMove = false;
	CanGuided = false;
	CurveTime = 1.2f;
	bUltimateBullet = false;
}

// Called when the game starts or when spawned
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::BoxCompBeginOverlap);

	AActor* FindActor = UGameplayStatics::GetActorOfClass(GetWorld(), ABeatNightPlayer::StaticClass());
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(FindActor);
	if(Player)
	{
		BulletLocation = GetActorLocation();
		PlayerLocation = Player->GetActorLocation();

		FVector NewLocation = PlayerLocation - BulletLocation;
		NewLocation.Normalize();
		Direction = NewLocation;
	}
	// 3초뒤 엑터가 존재하면 소멸
	GetWorld()->GetTimerManager().SetTimer(DestoryHandler, this, &AEnemyBullet::DestroyBullet, 3.f);
}

// Called every frame
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(CanMove)
	{
		if(CanGuided)
		{
			GuidedLocation(DeltaTime);
		}
		else
		{
			// 총알 플레이어에게
			FVector Location = Direction * BulletSpeed;
			SetActorLocation(GetActorLocation() + Location * DeltaTime);
		}
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
	ABeatNightPlayer* TargetPlayer = Cast<ABeatNightPlayer>(OtherActor);
	// 총 맞는 대상이 Player
	if(TargetPlayer)
	{
		// 총 맞는 위치에 파티클 생성
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PlayerBulletParticles, GetActorTransform()); 
		// Player에게 데미지 입힘
		if(Enemy)
		{
			// BossStage2 에서만 사용
			if(bUltimateBullet && Enemy->GetHpDown())
			{
				Enemy->SetUltimateDamaged(true);
				TargetPlayer->GetHitUlitmateParticle()->SetVisibility(true);
				TargetPlayer->GetHitUlitmateParticle2()->SetVisibility(true);
			}
			Enemy->DoDamage(TargetPlayer);
		}
		// 총알 제거
		Destroy();
	}
}

void AEnemyBullet::StartCurveBullet()
{
	CanGuided = true;
	GetWorldTimerManager().ClearTimer(ItemInerpTimer);
	GetWorldTimerManager().SetTimer(ItemInerpTimer, this, &AEnemyBullet::FinishGuided, CurveTime);
}

void AEnemyBullet::GuidedLocation(float DeltaTime)
{
	if(BulletCurve)
	{
		// 타이머의 경과 시간을 반환함, 타이머 핸들이 유효하지 않은 경우 -1을 반환
		const float ElapsedTime = GetWorldTimerManager().GetTimerElapsed(ItemInerpTimer);
		// 경과시간에 따른 커브값
		const float CurveValue = BulletCurve->GetFloatValue(ElapsedTime);
		// 총알 위치
		FVector InitLocoation = BulletLocation;
		// 총알과 캐릭터의 Z좌표 차이
		const FVector BulletToPlayer{FVector(0.f, 0.f, (PlayerLocation - InitLocoation).Z)};
		const float DeltaZ = BulletToPlayer.Size();
		const FVector CurrentLocation{ GetActorLocation() };
		
		const float InterpXValue = FMath::FInterpTo(CurrentLocation.X, PlayerLocation.X, DeltaTime, 4.0f);
		const float InterpYValue = FMath::FInterpTo(CurrentLocation.Y, PlayerLocation.Y, DeltaTime, 4.0f);

		InitLocoation.X = InterpXValue;
		InitLocoation.Y = InterpYValue;
		InitLocoation.Z += CurveValue * DeltaZ;
		SetActorLocation(InitLocoation);
	}
}

void AEnemyBullet::FinishGuided()
{
	CanGuided = false;
}

void AEnemyBullet::DestroyBullet()
{
	if(this) Destroy();
}

