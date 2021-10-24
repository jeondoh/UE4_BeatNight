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

bool AItem_Defense::BuyDefense(ABeatNightPlayer* Player)
{
	const uint8 PlayerCoin = Player->GetItemCoins();
	if(PlayerCoin >= ItemCoin)
	{
		Player->SetItemCoins(PlayerCoin - ItemCoin);
		Player->SetDefense(Player->GetDefense() + DefenseAmount);
		if(PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}
		Destroy();
		return true;
	}
	return false;
}

