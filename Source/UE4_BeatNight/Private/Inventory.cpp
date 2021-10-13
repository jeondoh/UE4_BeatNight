// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

#include "MontionActor.h"
#include "Weapon.h"
#include "Components/BoxComponent.h"

// Sets default values
AInventory::AInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(RootSceneComponent); 
	Slot1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot1"));
	Slot1->SetupAttachment(GetRootComponent());
	Slot2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot2"));
	Slot2->SetupAttachment(GetRootComponent());
	Slot3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot3"));
	Slot3->SetupAttachment(GetRootComponent());
	Slot4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot4"));
	Slot4->SetupAttachment(GetRootComponent());
	Slot5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot5"));
	Slot5->SetupAttachment(GetRootComponent());
	Slot6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Slot6"));
	Slot6->SetupAttachment(GetRootComponent());
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	CollisionBox->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();

	Slot1->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot1->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);

	Slot2->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot2->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);

	Slot3->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot3->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);

	Slot4->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot4->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);

	Slot5->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot5->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);

	Slot6->OnComponentBeginOverlap.AddDynamic(this, &AInventory::OverlapBeginSlot);
	Slot6->OnComponentEndOverlap.AddDynamic(this, &AInventory::OverlapEndSlot);
}

void AInventory::OverlapBeginSlot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor==nullptr) return;

	AMontionActor* MotionController = Cast<AMontionActor>(OtherActor);
	if(MotionController)
	{
		AActor* AttachedActor = MotionController->GetAttachedActor();
		if(AttachedActor)
		{
			
		}
	}
	
}

void AInventory::OverlapEndSlot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
