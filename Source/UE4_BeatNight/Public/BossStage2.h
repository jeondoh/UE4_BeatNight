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
	
private:
	/**************************************************************************************************/
	// 몽타주 & 애니메이션

	/** Target(Player)공격 몽타주 Play */
	UFUNCTION(BlueprintCallable)
	void PlayAttackToTargetMontage(FName Section);

	/**************************************************************************************************/
	// 보스 공격

	/** LineTrace 추적 */
	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult);

	/** 총(Gun) 공격 > 애니메이션 노티파이 */
	UFUNCTION(BlueprintCallable)
	void BossGunShot();

	/** 보스 공격 전 딜레이 시간 (각 섹션마다 대기시간 다름) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float DelayTime;

	/** 총알 스폰 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEnemyBullet> SpawnEnemyBullet;

	/** 보스 탄창 수(재장전 위함) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float AmmoCount;

	/** 보스 남은 총알 수 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float LastAmmo;

	/** 총알 속도 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float BulletSpeed;
	
	/** 몽타주 섹션 이름 */
	FName AttackSlow;
	FName AttackFast;
	FName AttackGuided;
	FName AttackUlitmate;

	/** 몽타주 섹션 이름 랜덤으로 반환 */
	UFUNCTION(BlueprintCallable)
	FName GetAttackSectionName();

	/**************************************************************************************************/
	// 이팩트

	/** 총알 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* BeamParticles;

	/**************************************************************************************************/
	
};
