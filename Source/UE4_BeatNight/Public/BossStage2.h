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
	
private:
	/**************************************************************************************************/
	// 몽타주 & 애니메이션

	/** Target(Player)공격 몽타주 Play */
	UFUNCTION(BlueprintCallable)
	void PlayAttackToTargetMontage(FName Section);

	/**************************************************************************************************/
	// 보스 공격

	/**  */
	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult);
	
	/** 총(Gun) 공격 > 애니메이션 노티파이 */
	UFUNCTION(BlueprintCallable)
	void BossGunShot();
	

	/**************************************************************************************************/
	// 이팩트

	/** 총알 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* BeamParticles;

	/**************************************************************************************************/
	
};
