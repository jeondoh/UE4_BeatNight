// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Key.h"

#include "BeatNightPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_Key::AItem_Key()
{
	BItemRotate = true;
}

void AItem_Key::AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AreaSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(ItemType == EItemType::EIT_Store)
	{
		return;
	}
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		int PlayerKeys = Player->GetItemKeys();
		Player->SetItemKeys(++PlayerKeys);
		Player->SetItemName(TEXT("KEY"));
		Player->ShowGetItemUI();
		if(PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}
		Destroy();
	}
}

bool AItem_Key::BuyKey(ABeatNightPlayer* Player)
{
	if(Player)
	{
		const uint8 PlayerCoin = Player->GetItemCoins();
		if(PlayerCoin >= ItemCoin)
		{
			Player->SetItemCoins(PlayerCoin - ItemCoin);
			int PlayerKeys = Player->GetItemKeys();
			Player->SetItemKeys(++PlayerKeys);
			if(PickupSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
			}
			Destroy();
			return true;
		}
	}
	return false;
}