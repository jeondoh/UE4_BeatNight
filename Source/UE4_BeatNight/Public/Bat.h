// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Bat.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ABat : public AEnemy
{
	GENERATED_BODY()

public:
	ABat();

private:
	/** 총알 스폰 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEnemyBullet> SpawnBullet;

	/** 총알 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float BulletSpeed;

	/** 공격 Delay 시간 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float DelayAttackTime;

	UFUNCTION(BlueprintCallable)
	void Attack();

	virtual void FinishDeath() override;
	
};
