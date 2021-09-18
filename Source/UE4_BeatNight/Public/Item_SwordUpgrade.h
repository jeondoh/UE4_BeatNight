// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponType.h"
#include "Item_SwordUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_SwordUpgrade : public AItem
{
	GENERATED_BODY()

public:
	AItem_SwordUpgrade();
	
private:
	virtual void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	ESwordType SetSwordUpgradeType(ESwordType Type);
	
};
