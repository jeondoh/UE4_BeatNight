// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStage2AnimInstance.h"

#include "BossStage2.h"
#include "Kismet/KismetMathLibrary.h"

UBossStage2AnimInstance::UBossStage2AnimInstance()
{
}

void UBossStage2AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(Boss == nullptr)
	{
		Boss = Cast<ABossStage2>(TryGetPawnOwner());
	}
	if(Boss)
	{
		FVector Velocity{Boss->GetVelocity()};
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
		bCanAttack = Boss->GetCanAttack();

		FRotator AimRotation = Boss->GetBaseAimRotation(); // 에임 위치
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Boss->GetVelocity()); // 캐릭터 이동 X좌표
		OffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}

void UBossStage2AnimInstance::ReloadFinish()
{
	Boss->SetCanAttack(true);
	bCanAttack = true;
}
