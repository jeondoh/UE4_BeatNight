// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "BeatNightPlayer.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(GetStaticMeshComponent());

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());

	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(GetRootComponent());

	// INIT
	BItemRotate = false; // 아이템 회전 여부
	RotateSpeed = 35.f; // 아이템 회전 속도
	ItemType = EItemType::EIT_Normal; // 아이템 타입
	ItemCoin = 0; // 아이템을 사기 위한 코인 개수
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AItem::BoxCollisionBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AItem::BoxCollisionEndOverlap);
	AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::AreaSphereBeginOverlap);
	AreaSphere->OnComponentEndOverlap.AddDynamic(this, &AItem::AreaSphereEndOverlap);
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 아이템 회전 (bRotate 여부에 따라)
	ItemRotate(DeltaTime);
}

void AItem::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;
	if(ItemType == EItemType::EIT_Normal) return;
	
	ABeatNightPlayer* CPlayer = Cast<ABeatNightPlayer>(OtherActor);
	if(CPlayer)
	{
		CastPlayer = CPlayer;
	}
}

void AItem::BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CastPlayer = nullptr;
}

void AItem::AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;
}

void AItem::AreaSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

bool AItem::BuyItem()
{
	if(CastPlayer && ItemType == EItemType::EIT_Store)
	{
		uint8 PlayerCoin = CastPlayer->GetItemCoins();
		if(PlayerCoin >= ItemCoin)
		{
			CastPlayer->SetItemCoins(PlayerCoin - ItemCoin);
			return true;
		}
	}
	return false;
}

void AItem::ItemRotate(float DeltaTime)
{
	if(BItemRotate)
	{
		FRotator NowRotation = GetActorRotation();
		NowRotation.Yaw += DeltaTime * RotateSpeed;
		SetActorRotation(NowRotation);
	}
}
