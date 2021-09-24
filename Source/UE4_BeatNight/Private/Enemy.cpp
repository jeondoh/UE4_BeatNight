// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Item.h"
#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
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
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	// 컴포넌트 오버랩 바인딩
	AgroSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AgroSphereBeginOverlap);
	AgroSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AgroSphereEndOverlap);
	AttackSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::AttackSphereBeginOverlap);
	AttackSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemy::AttackSphereEndOverlap);
}

void AEnemy::DoDamage(ABeatNightPlayer* Player)
{
	UGameplayStatics::ApplyDamage(Player, RandomizationDamage(EnemyDamage), EnemyController, this, UDamageType::StaticClass());
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
		EnemyController->RunBehaviorTree(BehaviorTree); // 루트노드에서 순차실행함.
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