// Fill out your copyright notice in the Description page of Project Settings.


#include "Rat.h"

#include "BeatNightPlayer.h"
#include "EnemyAIController.h"
#include "Components/SphereComponent.h"

ARat::ARat()
{
	RatAttackRange = false;
	RatAttackSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RatAttackSphere"));
	RatAttackSphere->SetupAttachment(GetRootComponent());
}

void ARat::BeginPlay()
{
	Super::BeginPlay();

	RatAttackSphere->OnComponentBeginOverlap.AddDynamic(this, &ARat::RatAttackSphereBeginOverlap);
	RatAttackSphere->OnComponentEndOverlap.AddDynamic(this, &ARat::RatAttackSphereEndOverlap);
}

void ARat::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
	}
}

void ARat::RatAttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor==nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		RatAttackRange = true;
	}
}

void ARat::RatAttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor==nullptr) return;
	
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		RatAttackRange = false;
	}
}

void ARat::RatAttack()
{
	if(RatAttackRange)
	{
		DoDamage(BeatNightPlayer);			
	}
}


