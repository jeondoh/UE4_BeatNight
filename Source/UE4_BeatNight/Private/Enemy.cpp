// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
// #include "Item.h"
#include "BeatNightPawn.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void AEnemy::DropItem()
{
	/*
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
	*/
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
		EnemyController->RunBehaviorTree(BehaviorTree); // 루트노드에서 순차실행함.
	}
}

void AEnemy::AgroSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;

	ABeatNightPawn* Player = Cast<ABeatNightPawn>(OtherActor);
	if(Player && EnemyController)
	{
		// 어그로 범위내에 Player가 들어오면 Blackboard의 Target을 Set
		if(EnemyController->GetBlackboardComponent())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), Player);
		}
	}
}


void AEnemy::AgroSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPawn* Player = Cast<ABeatNightPawn>(OtherActor);
	if(Player && EnemyController)
	{
		// 어그로 범위내에 Player가 없으면 Blackboard의 Target을 null 처리
		if(EnemyController->GetBlackboardComponent())
		{
			EnemyController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
		}
	}
}

void AEnemy::AttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;
	
	ABeatNightPawn* Player = Cast<ABeatNightPawn>(OtherActor);
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
	
	ABeatNightPawn* Player = Cast<ABeatNightPawn>(OtherActor);
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
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation));
}