// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossStage1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API UBossStage1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBossStage1AnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	class ABossStage1* Boss;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	float Speed;
};
