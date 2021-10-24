// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Coin.h"

#include "BeatNightPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AItem_Coin::AItem_Coin()
{
	BItemRotate = true;
}

void AItem_Coin::AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AreaSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		int PlayerCoins = Player->GetItemCoins();
		Player->SetItemCoins(++PlayerCoins);
		Player->SetItemName(TEXT("COIN"));
		Player->ShowGetItemUI();
		if(PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
		}
		Destroy();
	}
}
