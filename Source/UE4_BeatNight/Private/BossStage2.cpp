// Fill out your copyright notice in the Description page of Project Settings.

#include "BossStage2.h"

#include "Kismet/KismetMathLibrary.h"

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

void ABossStage2::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// 보스 스폰시 등장모션 몽타주 실행
	// PlayLevelMontage();
}

/*
void ABossStage2::PlayLevelMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && LevelMontage)
	{
		AnimInstance->Montage_Play(LevelMontage);
		AnimInstance->Montage_JumpToSection(FName("LevelStart"));
	}
}
*/
