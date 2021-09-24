// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Spider.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ASpider : public AEnemy
{
	GENERATED_BODY()

public:
	ASpider();

protected:
	virtual void BeginPlay() override;

private:
	/**************************************************************************************************/
	// 컴포넌트

	/** 왼쪽 다리 콜리전 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spider|Component", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class UBoxComponent* LeftLegCollision;
	/** 오른쪽 다리 콜리전 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Spider|Component", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class UBoxComponent* RightLegCollision;

	UFUNCTION(BlueprintCallable)
	void ActivateLeftLeg();
	UFUNCTION(BlueprintCallable)
	void DeactivateLeftLeg();
	UFUNCTION(BlueprintCallable)
	void ActivateRightLeg();
	UFUNCTION(BlueprintCallable)
	void DeactivateRightLeg();

	UFUNCTION()
	void LeftLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void RightLegBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**************************************************************************************************/
	// 속성

	/** 몬스터명(공격시 함수 Section명 불러올때 사용) */
	UPROPERTY(EditAnywhere, Category="Spider|Props", meta=(AllowPrivateAccess=true))
	FName SpiderName;

	UFUNCTION(BlueprintCallable)
	FName GetAttackSectionName();
	
	UFUNCTION()
	FName GetAttackJumpAttack();

	UFUNCTION()
	FName GetAttackIdleAttack();

	UFUNCTION()
	FName GetAttackWebAttack();
	
	UPROPERTY()	
	FName WebAttack;
	UPROPERTY()		
	FName JumpAttack;
	UPROPERTY()		
	FName idleAttack;

	UFUNCTION(BlueprintCallable)
	void StartAttack();
	
	UFUNCTION(BlueprintCallable)
	void EndAttack();

	UFUNCTION(BlueprintCallable)
	void PlayAttackMontage(FName Section);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spider|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* BeamParticles;
	
	UFUNCTION(BlueprintCallable)
	void WebToPlayerAttack();

	bool GetBeamEndLocation(const FVector& MuzzleSocketLocation, FHitResult& OutHitResult);
	
	/**************************************************************************************************/
	
};
