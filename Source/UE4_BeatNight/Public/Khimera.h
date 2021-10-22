// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Khimera.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AKhimera : public AEnemy
{
	GENERATED_BODY()

public:
	AKhimera();

protected:
	virtual void BeginPlay() override;

private: 
	/**************************************************************************************************/
	// 컴포넌트
	
	/** 왼손 칼 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Khimera|Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* LeftWeaponCollision;
	/** 오른손 칼 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Khimera|Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* RightWeaponCollision;

	// 무기 충돌 활성화/비활성화
	UFUNCTION(BlueprintCallable)
	void ActivateLeftWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftWeapon();
	UFUNCTION(BlueprintCallable)
	void ActivateRightWeapon();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightWeapon();

	// 공격 몽타주 이름
	FName AttackLFast;
	FName AttackRFast;
	FName AttackCFast;
	FName AttackL;
	FName AttackR;
	FName AttackRMB;

	/** CanMove 타이머 */
	UPROPERTY()
	FTimerHandle CanMoveHandler;
	
	UFUNCTION()
	void SetCanMove();

	UFUNCTION(BlueprintCallable)
	void StartAttack();

	UFUNCTION(BlueprintCallable)
	void EndAttack();

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage(FName Section);
	
	UFUNCTION(BlueprintCallable)
	FName GetAttackSectionName();

	UFUNCTION()
	void OnLeftWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
			
	UFUNCTION()
	void OnRightWeaponOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/**************************************************************************************************/
	
};
