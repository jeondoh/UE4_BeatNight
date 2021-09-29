// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BossStage1.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ABossStage1 : public AEnemy
{
	GENERATED_BODY()

public:
	ABossStage1();

protected:
	
private:

	virtual void FinishDeath() override;
	
};
