// Fill out your copyright notice in the Description page of Project Settings.


#include "Rat.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ARat::ARat()
{
	RatAttackRange = false;
}

void ARat::BeginPlay()
{
	Super::BeginPlay();
}

void ARat::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
	}
}

void ARat::RatAttack()
{
	if(EnemyController)
	{
		RatAttackRange = EnemyController->GetBlackboardComponent()->GetValueAsBool("InAttackRange");
		if(RatAttackRange)
		{
			DoDamage(BeatNightPlayer);			
		}
	}
}
