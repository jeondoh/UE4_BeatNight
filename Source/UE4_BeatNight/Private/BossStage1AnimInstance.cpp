// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStage1AnimInstance.h"

#include "BossStage1.h"

UBossStage1AnimInstance::UBossStage1AnimInstance()
{
}

void UBossStage1AnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if(Boss == nullptr)
	{
		Boss = Cast<ABossStage1>(TryGetPawnOwner());
	}
	if(Boss)
	{
		FVector Velocity{Boss->GetVelocity()};
		Velocity.Z = 0.f;
		Speed = Velocity.Size();
	}
}
