// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Defense.h"

#include "BeatNightPlayer.h"

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

	bool bGetItem = BuyItem();
	if(bGetItem)
	{
		CastPlayer->SetDefense(DefenseAmount);
		Destroy();
	}
	// TODO : 플레이어 Coin 부족 시 경고창 UI 생성
}
