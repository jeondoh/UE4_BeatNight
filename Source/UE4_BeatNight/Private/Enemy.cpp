// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Item.h"
#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "PotalActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// 변수 초기화
	InitalizedData();

	AgroSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AgroSphere"));
	AgroSphere->SetupAttachment(GetRootComponent());
	
	AttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackSphere"));
	AttackSphere->SetupAttachment(GetRootComponent());
	// 태그 추가
	Tags.Add(TagName);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	AgroSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	// 컴포넌트 오버랩 바인딩
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AgroSphereBeginOverlap);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AgroSphereEndOverlap);
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackSphereBeginOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AttackSphereEndOverlap);
}

void AEnemy::DoDamage(ABeatNightPlayer* Player)
{
	UGameplayStatics::ApplyDamage(Player, RandomizationDamage(EnemyDamage), EnemyController, this, UDamageType::StaticClass());
	if(bUlitmateDamaged)
	{
		DamagedPlayer = Player;
		GetWorldTimerManager().SetTimer(BossStage2Timer, this, &AEnemy::SetVisibilityPlayerParticle, UltimateDurationTime);		
	}
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(bDying) return 0;
	
	if(EnemyController)
	{
		// 타겟 어그로
		EnemyController->GetBlackboardComponent()->SetValueAsObject(FName("Target"), DamageCauser);
	}
	Health -= DamageAmount;
	if(Health <= 0.f)
	{
		Health = 0.f;
		Die();
	}
	return DamageAmount;
}

void AEnemy::SetVisibilityPlayerParticle()
{
	SetUltimateDamaged(false);
	DamagedPlayer->GetHitUlitmateParticle()->SetVisibility(false);
	DamagedPlayer->GetHitUlitmateParticle2()->SetVisibility(false);
}

void AEnemy::Die()
{
	if(bDying) return;
	bDying = true;
	// TODO 체력바 숨기기
	// HideHealthBar(); 
	// 사망 몽타주 실행
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && DeathMontage)
	{
		AnimInstance->Montage_Play(DeathMontage);
	}
	if(EnemyController)
	{
		EnemyController->GetBlackboardComponent()->SetValueAsBool(FName("Death"), true);
		EnemyController->GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);
		EnemyController->StopMovement();
	}
	// 아이템 드롭
	DropItem();
}

void AEnemy::FinishDeath()
{
	GetMesh()->bPauseAnims = true;
	GetWorldTimerManager().SetTimer(DeathTimer, this, &AEnemy::DestroyEnemy, DeathTime);
}

void AEnemy::DestroyEnemy()
{
	CheckDestroyEnemy(); // SpawnEnemy 엑터삭제
	Destroy();
}

void AEnemy::CheckDestroyEnemy()
{
	TArray<AActor*> arrOutActors;
	// BossStage1일 경우 
	if(MonsterName.IsEqual(TEXT("BossStage1")))
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), arrOutActors);
		if(arrOutActors.IsValidIndex(0))
		{
			// 월드에 남아있는 몬스터 전부 제거
			for(int i = 0; i < arrOutActors.Num(); ++i)
			{
				AEnemy* FindSpawnEnemy = dynamic_cast<AEnemy*>(arrOutActors[i]);
				if(FindSpawnEnemy)
				{
					FindSpawnEnemy->Destroy();
					// 아이템 드롭
					DropItem();	
				}
			}
		}
	}
	else
	{
		// 월드에 남아있는 몬스터 확인
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), TagName, arrOutActors);
		int MonsterNum = 0;
		if(arrOutActors.IsValidIndex(0))
		{
			for(int i = 0; i < arrOutActors.Num(); ++i)
			{
				AEnemy* FindSpawnEnemy = dynamic_cast<AEnemy*>(arrOutActors[i]);
				if(FindSpawnEnemy)
				{
					MonsterNum++;					
				}
			}
		}
		// 월드에 남아있는 몬스터가 없을 경우 포탈 작동하게
		if(MonsterNum==0){
			for(int i = 0; i < arrOutActors.Num(); ++i)
			{
				APotalActor* FindPotal = dynamic_cast<APotalActor*>(arrOutActors[i]);
				if(FindPotal)
				{
					FindPotal->SetbCanMove(true);
					FindPotal->GetPortalParticle()->SetVisibility(true);
				}
			}
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::InitalizedData()
{
	MaxHealth = 100.f; // 최대 체력
	Health = 100.f; // 체력
	EnemyDamage = 10.f; // 데미지
	bCanAttack = false; // 공격가능여부
	MoveToTargetRange = 70.f; // Move 범위
	bDying = false; // 사망여부
	DeathTime = 1.f; // 사망 후 destroy 간격시간
	bHPDown = false; // 남은 HP에 따라 변경(bossStage2에서만 사용)
	bUlitmateDamaged = false; // Player가 Ultimate 데미지를 받았을 경우(BossStage2에서만 사용)
	UlitmateDamaged = 10.f; // 추가 데미지
	UltimateDurationTime = 10.f; // BossStage2 Ulitmate 공격 지속시간
}

void AEnemy::DropItem()
{
	if(bDropItem && ItemType)
	{
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		// Enemy 위치에 스폰
		const FVector EnemyLocate = GetActorLocation();
		// 아이템 스폰
		GetWorld()->SpawnActor<AItem>(ItemType, EnemyLocate, GetActorRotation(), Param);
		// 아이템 드롭 사운드
		if(DropSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, DropSound, EnemyLocate);
		}
	}
}

void AEnemy::SetEnemyAIController()
{
	EnemyController = Cast<AEnemyAIController>(GetController());
	// 위치변환 (로컬->월드 좌표)
	const FVector WorldPatorlPoint = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint);
	const FVector WorldPatorlPoint2 = UKismetMathLibrary::TransformLocation(GetActorTransform(), PatrolPoint2);

	// BlackBoard에 변수 set
	if(EnemyController)
	{
		// ValueAs '' = 해당 타입의 변수값 Set
		EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint"), WorldPatorlPoint);
		EnemyController->GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolPoint2"), WorldPatorlPoint2);
		EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("EndAttack"), true);
		EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanMove"), true);
		EnemyController->RunBehaviorTree(BehaviorTree); // 루트노드에서 순차실행함.

		AgroSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		AttackSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AEnemy::AgroSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		// Player에 값 넣기
		BeatNightPlayer = Player;
		bCanAttack = true;
		
		if(EnemyController)
		{
			// 어그로 범위내에 Player가 들어오면 Blackboard의 Target을 Set
			if(EnemyController->GetBlackboardComponent())
			{
				EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Player);
				EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), bCanAttack);
			}	
		}
	}
}

void AEnemy::AgroSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		BeatNightPlayer = nullptr;
		bCanAttack = false;
		
		if(EnemyController)
		{
			// 어그로 범위내에 Player가 없으면 Blackboard의 Target을 null 처리
			if(EnemyController->GetBlackboardComponent())
			{
				EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
				EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("CanAttack"), bCanAttack);
			}
		}
	}
}

void AEnemy::AttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player && EnemyController)
	{
		// 어그로 범위내에 Player가 없으면 Blackboard의 Target을 null 처리
		if(EnemyController->GetBlackboardComponent())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), true);
		}
	}
}

void AEnemy::AttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player && EnemyController)
	{
		// 어그로 범위내에 Player가 없으면 Blackboard의 Target을 null 처리
		if(EnemyController->GetBlackboardComponent())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("InAttackRange"), false);
		}
	}
}

void AEnemy::GetLookAtRotation(FVector TargetLocation)
{
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	FRotator LookAtRotationYaw(0.f, LookAtRotation.Yaw, 0.f);
	// Target 방향으로 바라봄(보간)
	FRotator Rotator = FMath::RInterpTo(GetActorRotation(), LookAtRotationYaw, GetWorld()->GetDeltaSeconds(), 200.f);

	SetActorRotation(Rotator);
}

float AEnemy::RandomizationDamage(float Damage)
{
	return FMath::RandRange(Damage-10.f, Damage+30.f);
}