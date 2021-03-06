// Fill out your copyright notice in the Description page of Project Settings.

#include "BossStage2.h"

#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "EnemyBullet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

ABossStage2::ABossStage2()
{
	AttackSlow = TEXT("Attack_Slow");
	AttackFast = TEXT("Attack_Fast");
	AttackGuided = TEXT("Attack_Guided");
	AttackUlitmate = TEXT("Attack_Ultimate");
	AmmoCount = 4.f; // 탄창 수
	LastAmmo = AmmoCount; // 남은 총알 수
}

void ABossStage2::BeginPlay()
{
	Super::BeginPlay();
}

void ABossStage2::FinishDeath()
{
	Super::FinishDeath();
}

float ABossStage2::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(bDying) return 0;

	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(EnemyController)
	{
		// 타겟 어그로
		EnemyController->GetBlackboardComponent()->SetValueAsObject(FName("Target"), Player);
	}
	Health -= DamageAmount;
	CheckHP();
	if(Health <= 0.f)
	{
		Health = 0.f;
		SetVisibilityPlayerParticle(); // 파티클 제거
		Die();
		Player->SetGameClear(true);
		Player->ShowGameClearWidget();
	}
	return DamageAmount;
}

void ABossStage2::CheckHP()
{
	if(Health < 0) return;
	float HealthComp = MaxHealth * 0.4;
	// 피가 40% 미만일 경우 패턴변경 
	if(HealthComp > Health)
	{
		bHPDown = true;
		if(AttackHpDownMontage)
		{
			AttackMontage = nullptr;
		}
	}
}

void ABossStage2::PlayAttackToTargetMontage(FName Section)
{
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DelayTime"), DelayTime);
		}	
	}
	if(bCanAttack)
	{
		PlayAttackMontage(Section);
	}
}

void ABossStage2::PlayAttackMontage(FName Section)
{
	// 총알 없을 때 return
	if(LastAmmo <= 0)
	{
		bCanAttack = false;
		return;
	}
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AttackMontage == nullptr)
	{
		AttackMontage = AttackHpDownMontage;
	}
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

void ABossStage2::PlayReloadMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && ReloadMontage)
	{
		AnimInstance->Montage_Play(ReloadMontage);
		LastAmmo = AmmoCount; // 남은 총알 초기화
	}
}

void ABossStage2::PlayReloadParticle()
{
	// 리로드 파티클 생성
	if(ReloadParticles)
	{
		/*
		const USkeletalMeshSocket* ParticleSocket = GetMesh()->GetSocketByName("FX_Gun_Barrel");
		const FTransform SocketTransForm = ParticleSocket->GetSocketTransform(GetMesh());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ReloadParticles, SocketTransForm.GetLocation());
		*/
	}
}

void ABossStage2::BossGunShot()
{
	// Boss Enemy 총구 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("gun_MuzzleSocket");
	const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());
	// 총알스폰
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(SpawnBullet)
	{
		AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(SpawnBullet,
			SocketTransForm.GetLocation(), GetActorRotation(), Params);
		if(Bullet)
		{
			Bullet->SetBulletInfos(this, BulletSpeed);
			--LastAmmo; // 총알 수 줄어듬
		}
	}
}

void ABossStage2::BossFinishGunShot()
{
	// 총알이 없을 경우 Reload몽타주 실행
	if(LastAmmo <= 0)
	{
		bCanAttack = false;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if(AttackMontage == nullptr)
		{
			AttackMontage = AttackHpDownMontage;
		}
		AnimInstance->Montage_Stop(0.f, AttackMontage);
		PlayReloadMontage(); // 리로드 몽타주 실행
	}
}

void ABossStage2::BossUltimateAttack()
{
	// Boss Enemy 손 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("hand_r_ability_socket");
	const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());
	// 총알스폰
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(SpawnBulletUltimate)
	{
		AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(SpawnBulletUltimate,
			SocketTransForm.GetLocation(), GetActorRotation(), Params);
		if(Bullet)
		{
			Bullet->SetBulletInfos(this, BulletSpeed);			
		}
	}
}

void ABossStage2::BossGuidedMissile()
{
	// Boss Enemy 유도탄 발사 위치 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("Muzzle_04");
	const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());
	// 총알스폰
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const int GuidedBullet = bHPDown ? 7 : 5; // 유도탄 개수
	
	if(SpawnGuidedBullet)
	{
		// 유도탄 6개 소환
		for(int i=1; i<=GuidedBullet; i++)
		{
			const FVector SocketLocation = SocketTransForm.GetLocation();
			const float RandomFloat = FMath::RandRange(-500, 500);
			FVector RandomLocation = FVector(
				SocketLocation.X,
				SocketLocation.Y + RandomFloat,
				SocketLocation.Z
				);
			
			AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(SpawnGuidedBullet,
				RandomLocation, GetActorRotation(), Params);
			if(Bullet)
			{
				Bullet->SetBulletInfos(this, 0);
				Bullet->StartCurveBullet();				
			}
		}
	}
}

FName ABossStage2::GetAttackSectionName()
{
	FName SectionName;
	const int32 Section{FMath::RandRange(1, 100)};

	if(Section >= 1 && Section <= 40)
	{
		// 40%
		SectionName = AttackSlow;
		BulletSpeed = 1800.f; // 총알 속도
		DelayTime = 1.5f; // 대기시간
		EnemyDamage = bUlitmateDamaged ? 15.f + UlitmateDamaged : 15.f; // 데미지
	}
	else if(Section >= 41 && Section <=80)
	{
		// 40%
		SectionName = AttackFast;
		BulletSpeed = 2000.f; // 총알 속도
		DelayTime = 1.2f; // 대기시간
		EnemyDamage = bUlitmateDamaged ? 20.f + UlitmateDamaged : 20.f; // 데미지
	}
	else if(Section >= 81 && Section <=90)
	{
		// 10%
		SectionName = AttackGuided;
		DelayTime = 3.5f; // 대기시간
		EnemyDamage = bUlitmateDamaged ? 15.f + UlitmateDamaged : 15.f; // 데미지
	}
	else
	{
		// 10%
		SectionName = AttackUlitmate;
		DelayTime = 3.5f; // 대기시간
		BulletSpeed = 2200.f; // 총알 속도
		EnemyDamage = bUlitmateDamaged ? 50.f + UlitmateDamaged : 50.f; // 데미지
	} 
	return SectionName;
}