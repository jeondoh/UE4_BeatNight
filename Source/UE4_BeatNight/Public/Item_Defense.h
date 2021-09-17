// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Defense.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_Defense : public AItem
{
	GENERATED_BODY()
	
public:
	AItem_Defense();
	
private:
	virtual void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	/**************************************************************************************************/
	// 속성
	
	/** 방어력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Defense|Props", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	float DefenseAmount;
	
};
