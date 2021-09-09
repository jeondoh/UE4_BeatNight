// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStage2AnimInstance.h"

#include "BossStage2.h"

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
	}
}
