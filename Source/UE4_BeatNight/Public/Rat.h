// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Rat.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ARat : public AEnemy
{
	GENERATED_BODY()

public:
	ARat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void RatAttack();

	UPROPERTY()
	bool RatAttackRange;
};
