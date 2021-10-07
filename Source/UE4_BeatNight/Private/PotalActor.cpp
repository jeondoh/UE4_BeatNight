// Fill out your copyright notice in the Description page of Project Settings.


#include "PotalActor.h"

#include "BeatNightPlayer.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APotalActor::APotalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComponent->SetupAttachment(GetRootComponent());

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(GetRootComponent());

	PortalParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PortalParticle"));
	PortalParticle->SetupAttachment(GetRootComponent());

	bCanMove = false;
	PortalParticle->SetVisibility(false);
}

// Called when the game starts or when spawned
void APotalActor::BeginPlay()
{
	Super::BeginPlay();

	const FVector ArrowLocation{Arrow->GetForwardVector()};
	MoveToLocation = GetActorLocation() + ArrowLocation * -500;
	
	Tags.Add(TagName);
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APotalActor::BoxCompBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &APotalActor::BoxCompEndOverlap);
}

void APotalActor::BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;

	if(bCanMove)
	{
		ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
		if(Player)
		{
			PlayLevelSeq(Player);
		}
	}
}

void APotalActor::BoxCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor  == nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		bCanMove = true;
	}
}