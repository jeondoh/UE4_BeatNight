// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BossStage2.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ABossStage2 : public AEnemy
{
	GENERATED_BODY()

public:
	ABossStage2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void PostInitializeComponents() override;
	
private:
	/**************************************************************************************************/
	// 몽타주 & 애니메이션

	/*
	// 보스 스폰시 등장 몽타주 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Animate", meta=(AllowPrivateAccess=true))
	UAnimMontage* LevelMontage;
	
	void PlayLevelMontage();
	*/

	/**************************************************************************************************/	
};
