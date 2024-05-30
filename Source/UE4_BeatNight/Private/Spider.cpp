// Fill out your copyright notice in the Description page of Project Settings.


#include "Spider.h"

#include "BeatNightPlayer.h"
#include "DrawDebugHelpers.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ASpider::ASpider()
{
	LeftLegCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftLegBox"));
	LeftLegCollision->SetupAttachment(GetMesh(), FName("LeftLegBone"));
	
	RightLegCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightLegBox"));
	RightLegCollision->SetupAttachment(GetMesh(), FName("RightLegBone"));

	SpiderName = TEXT("Spider");
	WebAttack = TEXT("WebAttack");
	JumpAttack = TEXT("JumpAttack");
	idleAttack = TEXT("idleAttack");
	WebTime = 3.f;
	PlayerSlowMovement = 0.1f;
}

void ASpider::BeginPlay()
{
	Super::BeginPlay();

	LeftLegCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpider::LeftLegBeginOverlap);
	RightLegCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpider::RightLegBeginOverlap);
	
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	
	LeftLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftLegCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	LeftLegCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftLegCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightLegCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	RightLegCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightLegCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Player)
	{
		PlayerMovement = Player->GetMovementSpeed();		
	}
}

void ASpider::ActivateLeftLeg()
{
	LeftLegCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASpider::DeactivateLeftLeg()
{
	LeftLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpider::ActivateRightLeg()
{
	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ASpider::DeactivateRightLeg()
{
	RightLegCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpider::LeftLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		DoDamage(Player); // 데미지 입힘
	}
}

void ASpider::RightLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		DoDamage(Player); // 데미지 입힘
	}
}

void ASpider::PlayAttackMontage(FName Section)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(Section, AttackMontage);
	}
}

void ASpider::WebToPlayerSlow()
{
	SlowPlayer->SetMovementSpeed(PlayerMovement);
	SlowPlayer = nullptr;
}

void ASpider::StartAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", false);
	}
}

void ASpider::EndAttack()
{
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool("EndAttack", true);
	}
}

FName ASpider::GetAttackSectionName()
{
	FName Section = TEXT("");
	
	if(SpiderName.IsEqual(TEXT("Spider")))
	{
		Section = GetAttackIdleAttack();
	}
	else if(SpiderName.IsEqual("SpiderWeb"))
	{
		Section = GetAttackWebAttack();
	}
	else if(SpiderName.IsEqual("SpiderJump"))
	{
		Section = GetAttackJumpAttack();
	}
	if(EnemyController)
	{
		if(EnemyController->GetBlackboardComponent())
		{
			// 공격 이후 DelayTime
			EnemyController->GetBlackboardComponent()->SetValueAsFloat(TEXT("DelayTime"), DelayTime);
			// DelayTime 이후에 움직임 가능하게 설정
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), false);
			GetWorldTimerManager().SetTimer(CanMoveHandler, this, &ASpider::SetCanMove, DelayTime);
		}	
	}
	return Section;
}

void ASpider::SetCanMove()
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

FName ASpider::GetAttackJumpAttack()
{
	EnemyDamage = 15.f;
	DelayTime = 2.f; // 대기시간
	return JumpAttack;
}

FName ASpider::GetAttackIdleAttack()
{
	EnemyDamage = 10.f;
	DelayTime = 2.f; // 대기시간
	return idleAttack;
}

FName ASpider::GetAttackWebAttack()
{
	EnemyDamage = 0.f;
	DelayTime = 10.f; // 대기시간
	return WebAttack;
}

bool ASpider::GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult)
{
	// 라인 추적 : 물체가 거미 입위치와 끝점을 지정해 충돌여부 확인
	const FVector MuzzleTraceStart{MuzzleSocketLocation};
	const FVector EnemyForwardLocation{GetActorForwardVector()};

	// FVector TraceEnd = BeatNightPlayer->GetActorLocation() + EnemyForwardLocation * 1000.f;
	FVector NewLocation = BeatNightPlayer->GetActorLocation() - MuzzleTraceStart;
	FVector TraceEnd = MuzzleTraceStart + NewLocation + EnemyForwardLocation * 100.f;
	
	GetWorld()->LineTraceSingleByChannel(OutHitResult, MuzzleTraceStart, TraceEnd, ECollisionChannel::ECC_Pawn);
	
	// DrawDebugLine(GetWorld(), MuzzleTraceStart, TraceEnd, FColor::Red, false, 2.0f, 0, 1.0f);
	
	// 라인 추적 사이에 Actor가 존재하면
	if(OutHitResult.bBlockingHit)
	{
		return true;
	}
	return false;
}

void ASpider::WebToPlayerAttack()
{
	// Spider 입 소켓 가져오기
	const USkeletalMeshSocket* MuzzleSocket = GetMesh()->GetSocketByName("mouthSocket");
	if(MuzzleSocket)
	{
		const FTransform SocketTransForm = MuzzleSocket->GetSocketTransform(GetMesh());

		FHitResult BeamHitResult;
		bool bBeamEnd = GetBeamEndLocation(SocketTransForm.GetLocation(), BeamHitResult);
		if(bBeamEnd)
		{
		    ABeatNightPlayer* HitPlayer = Cast<ABeatNightPlayer>(BeamHitResult.GetActor());
		    if(HitPlayer){
		    	SlowPlayer = HitPlayer;
				HitPlayer->SetMovementSpeed(PlayerSlowMovement);
		    	GetWorldTimerManager().SetTimer(WebHandler, this, &ASpider::WebToPlayerSlow, WebTime); // 캐릭터 이동속도 복구 
		    }
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


