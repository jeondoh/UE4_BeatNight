// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_SwordUpgrade.h"

#include "BeatNightPlayer.h"
#include "Weapon_Sword.h"

AItem_SwordUpgrade::AItem_SwordUpgrade()
{
	BItemRotate = true;
}

void AItem_SwordUpgrade::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::BoxCollisionBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                SweepResult);
	bool bGetItem = BuyItem();
	if(bGetItem)
	{
		// TODO : 인벤토리에서 Sword 찾고 업그레이드 로직
		// 임시
		TArray<AWeapon*> Weapons = CastPlayer->GetInventory();
		for(AWeapon* Weapon : Weapons)
		{
			AWeapon_Sword* Sword = Cast<AWeapon_Sword>(Weapon);
			if(Sword)
			{
				ESwordType GetType = Sword->GetSwordType();
				if(GetType == ESwordType::EST_Level4) continue; // LEVEL4가 최대

				Sword->SetSwordType(SetSwordUpgradeType(GetType));
				Sword->SetWeaponDataTable();
			}
		}
		Destroy();
	}
	// TODO : 플레이어 Coin 부족 시 경고창 UI 생성
}

ESwordType AItem_SwordUpgrade::SetSwordUpgradeType(ESwordType Type)
{
	switch(Type)
	{
		case ESwordType::EST_Level1:
			return ESwordType::EST_Level2;
		case ESwordType::EST_Level2:
			return ESwordType::EST_Level3;
		case ESwordType::EST_Level3:
			return ESwordType::EST_Level4;
	}
	return ESwordType::EST_Level1;
}


