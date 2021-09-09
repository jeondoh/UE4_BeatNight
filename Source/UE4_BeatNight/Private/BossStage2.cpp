// Fill out your copyright notice in the Description page of Project Settings.

#include "BossStage2.h"

#include "BeatNightPawn.h"
#include "DrawDebugHelpers.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABossStage2::ABossStage2()
{
}

void ABossStage2::BeginPlay()
{
	Super::BeginPlay();
}

void ABossStage2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ABossStage2::PlayAttackToTargetMontage(FName Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

bool ABossStage2::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult)
{
	// 라인 추적 : 물체가 총구위치와 끝점을 지정해 충돌여부 확인
	const FVector WeaponTraceStart{MuzzleSocketLocation};
	const FVector PlayerLocation{BeatNightPlayer->GetActorLocation()};
	
	FVector WeaponTraceEnd = PlayerLocation; 
	
	GetWorld()->LineTraceSingleByChannel(OutHitResult, WeaponTraceStart, WeaponTraceEnd, ECollisionChannel::ECC_Visibility);

	DrawDebugLine(GetWorld(), WeaponTraceStart, WeaponTraceEnd, FColor::Red, false, 2.0f, 0, 1.0f);
	// 라인 추적 사이에 Actor가 존재하면
	if(OutHitResult.bBlockingHit)
	{
		return true;
	}
	return false;
}

void ABossStage2::BossGunShot()
{
	// Boss Enemy 총구 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("gun_MuzzleSocket");
	if(MuzzleSocket)
	{
		const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());

		FHitResult BeamHitResult;
		bool bBeamEnd = GetBeamEndLocation(SocketTransForm.GetLocation(), BeamHitResult);
		if(bBeamEnd)
		{
			UE_LOG(LogTemp, Error, TEXT("HIT@@"));
		}
		// 총알 발사 경로에 이팩트 생성
		if(BeamParticles)
		{
			UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, SocketTransForm.GetLocation());
			if(Beam)
			{
				Beam->SetVectorParameter(FName("Target"), BeamHitResult.Location); // 이미터 > 타겟 > 타겟이름(Target)
			}
		}
	}
}
