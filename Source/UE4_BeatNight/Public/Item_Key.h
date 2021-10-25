// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Key.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_Key : public AItem
{
	GENERATED_BODY()
	
public:
	AItem_Key();

	bool BuyKey(class ABeatNightPlayer* Player);

private:
	virtual void AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
