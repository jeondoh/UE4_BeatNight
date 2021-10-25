// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_SwordUpgrade.h"

#include "BeatNightPlayer.h"
#include "Weapon_Sword.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_SwordUpgrade::AItem_SwordUpgrade()
{
	BItemRotate = true;
}

int AItem_SwordUpgrade::UpgradeSword(ABeatNightPlayer* Player)
{
	const uint8 PlayerCoin = Player->GetItemCoins();
	if(PlayerCoin >= ItemCoin)
	{
		// 인벤토리에서 Sword 찾고 업그레이드
		TArray<AWeapon*> Weapons = Player->GetInventory();
		for(AWeapon* Weapon : Weapons)
		{
			AWeapon_Sword* Sword = Cast<AWeapon_Sword>(Weapon);
			if(Sword)
			{
				const ESwordType GetType = Sword->GetSwordType();
				if(GetType == ESwordType::EST_Level3) continue;
				if(GetType == ESwordType::EST_Level4) continue; // LEVEL4가 최대

				Sword->SetSwordType(SetSwordUpgradeType(GetType));
				Sword->SetWeaponDataTable();
				if(PickupSound)
				{
					UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
				}
				Player->SetItemCoins(PlayerCoin - ItemCoin);
				Destroy();
				return 1;
			}
		}
		return 2;
	}
	return 0;
}

ESwordType AItem_SwordUpgrade::SetSwordUpgradeType(ESwordType Type)
{
	switch(Type)
	{
		case ESwordType::EST_Level1:
			return ESwordType::EST_Level2;
		case ESwordType::EST_Level2:
			return ESwordType::EST_Level3;
	}
	return ESwordType::EST_Level1;
}


