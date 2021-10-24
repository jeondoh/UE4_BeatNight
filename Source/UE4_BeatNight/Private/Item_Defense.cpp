// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Defense.h"

#include "BeatNightPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_Defense::AItem_Defense()
{
	DefenseAmount = 0.f;
	BItemRotate = true;
}

void AItem_Defense::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BoxCollisionBeginOverlap(OverlappedComponent, OtherActor, OtherComp,
		OtherBodyIndex, bFromSweep, SweepResult);

	/*
	bool bGetItem = BuyItem();
	if(bGetItem)
	{
		CastPlayer->SetDefense(DefenseAmount);
		if(PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}
		Destroy();
	}
	*/
}
