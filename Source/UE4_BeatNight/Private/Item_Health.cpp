// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_Health.h"

#include "BeatNightPlayer.h"


AItem_Health::AItem_Health()
{
	HealthAmount = 0.f;
	BItemRotate = true;
}

void AItem_Health::AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::AreaSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(OtherActor);
	if(Player)
	{
		float MaxHealth = Player->GetMaxHealth();
		float Health = Player->GetHealth();

		float PlayerHeal = Health + HealthAmount; 
		if(PlayerHeal >= MaxHealth)
		{
			PlayerHeal = MaxHealth;
		}
		Player->SetHealth(PlayerHeal);
		Destroy();
	}
}
