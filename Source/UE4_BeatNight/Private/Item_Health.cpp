// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Health.h"

#include "BeatNightPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"


AItem_Health::AItem_Health()
{
	HealthAmount = 0.f;
	BItemRotate = true;
}

void AItem_Health::AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AreaSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(ItemType == EItemType::EIT_Normal)
	{
		ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
		HealPlayer(Player);
	}
}

bool AItem_Health::HealPlayer(ABeatNightPlayer* Player)
{
	if(Player)
	{
		const uint8 PlayerCoin = Player->GetItemCoins();
		if(PlayerCoin >= ItemCoin)
		{
			Player->SetItemCoins(PlayerCoin - ItemCoin);
			const float MaxHealth = Player->GetMaxHealth();
			const float Health = Player->GetHealth();

			float PlayerHeal = Health + HealthAmount; 
			if(PlayerHeal >= MaxHealth)
			{
				PlayerHeal = MaxHealth;
			}
			Player->SetHealth(PlayerHeal);
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
