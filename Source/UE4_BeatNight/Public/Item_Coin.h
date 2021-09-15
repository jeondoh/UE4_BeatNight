// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Coin.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_Coin : public AItem
{
	GENERATED_BODY()

public:
	AItem_Coin();

private:

	virtual void AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	/**************************************************************************************************/
	// 이팩트
	
	/** 획득 사운드 */
	UPROPERTY(EditAnywhere, Category = "Coins|Effect", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class USoundCue* GotSound;

	
};
