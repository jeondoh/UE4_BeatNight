// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

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
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 아이템 회전 (bRotate 여부에 따라)
	ItemRotate(DeltaTime);
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

