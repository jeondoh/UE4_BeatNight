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
	virtual void BeginPlay() override;

private:
	
	/** 근접공격 범위 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Component", meta=(AllowPrivateAccess=true))
	class USphereComponent* MeleeRangeSphere;

	/** 총알 스폰 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEnemyBullet> SpawnBullet;

	/** 총알 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float BulletSpeed;

	/** 총알 속도 */
	bool bCanMeleeAttack;

	/** 오른쪽 다리 콜리전 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Boss|Component", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class UBoxComponent* RightLegCollision;

	UFUNCTION(BlueprintCallable)
	void ActivateRightLeg();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightLeg();

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage(FName Section);

	UFUNCTION(BlueprintCallable)
	void BossFire();
	
	UFUNCTION(BlueprintCallable)
	void SpawnSpider();

	UFUNCTION(BlueprintCallable)
	FName GetAttackSectionName();

	/** CanMove 타이머 */
	UPROPERTY()
	FTimerHandle CanMoveHandler;
	
	UFUNCTION()
	void SetCanMove();
	
	virtual void FinishDeath() override;

	UFUNCTION()
	void RightLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttackMeleeSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttackMeleeSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
