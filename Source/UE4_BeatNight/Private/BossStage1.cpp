// Fill out your copyright notice in the Description page of Project Settings.


#include "BossStage1.h"

#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "EnemyBullet.h"
#include "SpawnSpiderEnemy.h"
#include "Spider.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

ABossStage1::ABossStage1()
{
	MeleeRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackMeleeSphere"));
	MeleeRangeSphere->SetupAttachment(GetRootComponent());
	bCanMeleeAttack = false;

	RightLegCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegBox"));
	RightLegCollision->SetupAttachment(GetMesh(), FName("RightLegBone"));
}

void ABossStage1::BeginPlay()
{
	Super::BeginPlay();

	MeleeRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ABossStage1::AttackMeleeSphereBeginOverlap);
	MeleeRangeSphere->OnComponentEndOverlap.AddDynamic(this, &ABossStage1::AttackMeleeSphereEndOverlap);
	RightLegCollision->OnComponentBeginOverlap.AddDynamic(this, &ABossStage1::RightLegBeginOverlap);

	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLegCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightLegCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightLegCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ABossStage1::AttackMeleeSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;

	ABeatNightPlayer* CPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CPlayer)
	{
		bCanMeleeAttack = true;
	}
}

void ABossStage1::AttackMeleeSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == nullptr) return;

	ABeatNightPlayer* CPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CPlayer)
	{
		bCanMeleeAttack = false;
	}
}

void ABossStage1::FinishDeath()
{
	Super::FinishDeath();
}

void ABossStage1::BossFire()
{
	// Boss Enemy ?????? ????????????
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("LeftHandSocket");
	const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());
	// ??????
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if(SpawnBullet)
	{
		AEnemyBullet* Bullet = GetWorld()->SpawnActor<AEnemyBullet>(SpawnBullet,
			SocketTransForm.GetLocation(), GetActorRotation(), Params);
		if(Bullet)
		{
			Bullet->SetBulletInfos(this, BulletSpeed);
		}
	}
}

void ABossStage1::SpawnSpider()
{
	TArray<AActor*> Arr;
	TArray<AActor*> EnemyArr;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnSpiderEnemy::StaticClass(), Arr);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpider::StaticClass(), EnemyArr);

	if(Arr.IsValidIndex(0))
	{
		int SpawnEnemy = 0;
		bool bSpawn = true;

		for(int i = 0; i < EnemyArr.Num(); ++i)
		{
			ASpider* FindSpawnEnemy = dynamic_cast<ASpider*>(EnemyArr[i]);
			if(FindSpawnEnemy)
			{
				SpawnEnemy++;
			}
		}
		if(SpawnEnemy >= 6)
		{
			bSpawn = false;
		}
		if(bSpawn)
		{
			for(int i = 0; i < Arr.Num(); ++i)
			{
				ASpawnSpiderEnemy* FindSpawnActor = dynamic_cast<ASpawnSpiderEnemy*>(Arr[i]);
				if(FindSpawnActor)
				{
					FindSpawnActor->bDropItem = false;
					FindSpawnActor->SpawnEnemy();				
				}
			}	
		}
	}
}

void ABossStage1::ActivateRightLeg()
{
	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ABossStage1::DeactivateRightLeg()
{
	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABossStage1::PlayAttackMontage(FName Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

FName ABossStage1::GetAttackSectionName()
{
	FName SectionName;
	const int32 Section{FMath::RandRange(1, 100)};

	if(bCanMeleeAttack)
	{
		EnemyDamage = 20.f;
		DelayTime = 2.f; // ????????????
		SectionName = TEXT("MeleeAttack");
	}
	else
	{
		if(Section >= 1 && Section <= 85)
		{
			SectionName = TEXT("AttackRange");
			BulletSpeed = 1000.f; // ?????? ??????
			DelayTime = 2.f; // ????????????
			EnemyDamage = 15.f; // ?????????
		}
		else
		{
			SectionName = TEXT("AttackSpawn");
			DelayTime = 3.f; // ????????????
			EnemyDamage = 0.f; // ?????????
		}
	}
	
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// ?????? ?????? DelayTime
			EnemyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DelayTime"), DelayTime);
			// DelayTime ????????? ????????? ???????????? ??????
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), false);
			GetWorldTimerManager().SetTimer(CanMoveHandler, this, &ABossStage1::SetCanMove, DelayTime);
		}
	}
	return SectionName;
}

void ABossStage1::RightLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		DoDamage(Player); // ????????? ??????
	}
}

void ABossStage1::SetCanMove()
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