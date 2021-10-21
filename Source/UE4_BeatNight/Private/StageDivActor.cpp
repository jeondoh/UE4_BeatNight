// Fill out your copyright notice in the Description page of Project Settings.


#include "StageDivActor.h"

#include "BeatNightPlayer.h"
#include "Enemy.h"
#include "PotalActor.h"
#include "SpawnEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStageDivActor::AStageDivActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	BoxComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AStageDivActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AStageDivActor::BoxBeginOverlap);
}

void AStageDivActor::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;

	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		Player->SetPlayerStageName(StageName); // 현재 플레이어 레벨 정보 SET

		TArray<AActor*> arrOutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), StageName, arrOutActors);

		int MonsterNum = 0;
		
		if(arrOutActors.IsValidIndex(0))
		{
			for(int i = 0; i < arrOutActors.Num(); ++i)
			{
				ASpawnEnemy* FindSpawnEnemy = dynamic_cast<ASpawnEnemy*>(arrOutActors[i]);
				if(FindSpawnEnemy)
				{
					FindSpawnEnemy->SpawnEnemy();
					FindSpawnEnemy->Destroy();
				}
			}
		}

		TArray<AActor*> arrOutActors2;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), arrOutActors2);
		
		for(int i = 0; i < arrOutActors2.Num(); ++i)
		{
			AEnemy* FindEnemy = dynamic_cast<AEnemy*>(arrOutActors2[i]);
			if(FindEnemy)
			{
				MonsterNum++;					
			}
		}
		if(MonsterNum == 0)
		{
			for(int i = 0; i < arrOutActors.Num(); ++i)
			{
				APotalActor* FindPotal = dynamic_cast<APotalActor*>(arrOutActors[i]);
				if(FindPotal)
				{
					FindPotal->OpenDoor();
					FindPotal->SetbCanMove(true);
				}				
			}
		}
		
	}
	
}