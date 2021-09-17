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

	
private:
	virtual void AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	/**************************************************************************************************/
	// 이팩트
	
	/** 획득 사운드 */
	UPROPERTY(EditAnywhere, Category = "Health|Effect", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class USoundCue* GotSound;

	/**************************************************************************************************/
	// 속성
	
	/** 회복량 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health|Props", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	float HealthAmount;

	/**************************************************************************************************/
	// 기능

	/** 캐릭터 회복 */
	UFUNCTION()
	void HealPlayer(class ABeatNightPlayer* Player);
	
};
