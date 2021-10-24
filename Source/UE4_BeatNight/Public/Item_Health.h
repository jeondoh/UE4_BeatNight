// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Health.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_Health : public AItem
{
	GENERATED_BODY()

public:
	AItem_Health();

	/** 캐릭터 회복 */
	UFUNCTION(BlueprintCallable)
	bool HealPlayer(class ABeatNightPlayer* Player);
	
private:
	virtual void AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	/**************************************************************************************************/
	// 속성
	
	/** 회복량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Props", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	float HealthAmount;
	
};
