// Fill out your copyright notice in the Description page of Project Settings.


#include "Khimera.h"

#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"

AKhimera::AKhimera()
{
	LeftWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWeaponBox"));
	LeftWeaponCollision->SetupAttachment(GetMesh(), FName("LeftWeaponBone"));
	RightWeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWeaponBox"));
	RightWeaponCollision->SetupAttachment(GetMesh(), FName("RightWeaponBone"));

	AttackRMB = TEXT("AttackRMB");
	AttackLFast = TEXT("AttackLFast");
	AttackRFast = TEXT("AttackRFast");
	AttackCFast = TEXT("AttackCFast");
	AttackL = TEXT("AttackL");
	AttackR = TEXT("AttackR");
}

void AKhimera::BeginPlay()
{
	Super::BeginPlay();

	LeftWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AKhimera::OnLeftWeaponOverlap);
	RightWeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AKhimera::OnRightWeaponOverlap);

	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightWeaponCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightWeaponCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightWeaponCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void AKhimera::ActivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AKhimera::DeactivateLeftWeapon()
{
	LeftWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKhimera::ActivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AKhimera::DeactivateRightWeapon()
{
	RightWeaponCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKhimera::PlayAttackMontage(FName Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

FName AKhimera::GetAttackSectionName()
{
	FName SectionName;
	const int32 Section{FMath::RandRange(1, 6)};
	switch(Section)
	{
	case 1:
		SectionName = AttackLFast;
		DelayTime = 1.5f; // ????????????
		break;
	case 2:
		SectionName = AttackRFast;
		DelayTime = 1.5f; // ????????????
		break;
	case 3:
		SectionName = AttackCFast;
		DelayTime = 1.5f; // ????????????
		break;
	case 4:
		SectionName = AttackRMB;
		DelayTime = 1.5f; // ????????????
		break;
	case 5:
		SectionName = AttackR;
		DelayTime = 2.0f; // ????????????
		break;
	case 6:
		SectionName = AttackRMB;
		DelayTime = 2.0f; // ????????????
		break;
	}
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// ?????? ?????? DelayTime
			EnemyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DelayTime"), DelayTime);
			// DelayTime ????????? ????????? ???????????? ??????
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), false);
			GetWorldTimerManager().SetTimer(CanMoveHandler, this, &AKhimera::SetCanMove, DelayTime);
		}
	}
	return SectionName;
}

void AKhimera::SetCanMove()
{
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// DelayTime ????????? ????????? ???????????? ??????
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), true);
			GetWorldTimerManager().ClearTimer(CanMoveHandler);
		}	
	}
}

void AKhimera::StartAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", false);
	}
}

void AKhimera::EndAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", true);
	}
}

void AKhimera::OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* CastPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CastPlayer)
	{
		DoDamage(CastPlayer);
	}
	
}

void AKhimera::OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* CastPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CastPlayer)
	{
		DoDamage(CastPlayer);
	}
}
