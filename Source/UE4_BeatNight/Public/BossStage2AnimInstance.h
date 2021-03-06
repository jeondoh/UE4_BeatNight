// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BossStage2AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API UBossStage2AnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBossStage2AnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties(float DeltaTime);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	class ABossStage2* Boss;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	bool bCanAttack;
	
	/** 이동 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Anim|Info", meta=(AllowPrivateAccess=true))
	float OffsetYaw;

	/** Reload 완료 > 노티파이 */
	UFUNCTION(BlueprintCallable)
	void ReloadFinish();
};
