// Fill out your copyright notice in the Description page of Project Settings.


#include "Grux.h"

#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"

AGrux::AGrux()
{
	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWeaponBox"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("LeftWeaponBone"));
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWeaponBox"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));

	AttackLFast = TEXT("AttackLFast");
	AttackRFast = TEXT("AttackRFast");
	AttackL = TEXT("AttackL");
	AttackR = TEXT("AttackR");
}

void AGrux::BeginPlay()
{
	Super::BeginPlay();

	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrux::OnLeftWeaponOverlap);
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AGrux::OnRightWeaponOverlap);

	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AGrux::ActivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGrux::DeactivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGrux::ActivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AGrux::DeactivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGrux::PlayAttackMontage(FName Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

FName AGrux::GetAttackSectionName()
{
	FName SectionName;
	const int32 Section{FMath::RandRange(1, 4)};
	switch(Section)
	{
	case 1:
		SectionName = AttackLFast;
		DelayTime = 1.5f; // 대기시간
		break;
	case 2:
		SectionName = AttackRFast;
		DelayTime = 1.5f; // 대기시간
		break;
	case 3:
		SectionName = AttackR;
		DelayTime = 1.5f; // 대기시간
		break;
	case 4:
		SectionName = AttackL;
		DelayTime = 1.5f; // 대기시간
		break;
	}
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// 공격 이후 DelayTime
			EnemyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DelayTime"), DelayTime);
			// DelayTime 이후에 움직임 가능하게 설정
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), false);
			GetWorldTimerManager().SetTimer(CanMoveHandler, this, &AGrux::SetCanMove, DelayTime);
		}
	}
	return SectionName;
}

void AGrux::SetCanMove()
{
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// DelayTime 이후에 움직임 가능하게 설정
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), true);
			GetWorldTimerManager().ClearTimer(CanMoveHandler);
		}	
	}
}

void AGrux::StartAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", false);
	}
}

void AGrux::EndAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", true);
	}
}

void AGrux::OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* CastPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CastPlayer)
	{
		DoDamage(CastPlayer);
	}
	
}

void AGrux::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* CastPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CastPlayer)
	{
		DoDamage(CastPlayer);
	}
}
