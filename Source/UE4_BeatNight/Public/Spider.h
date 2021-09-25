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

	UPROPERTY()
	class ABeatNightPlayer* SlowPlayer;
	UPROPERTY()
	FTimerHandle WebHandler;
	/** 캐릭터가 느려지기전 원래 속도 */
	UPROPERTY()
	float PlayerMovement;
	/** 캐릭터가 느려지는 이동속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spider|Attack", meta=(AllowPrivateAccess=true))
	float PlayerSlowMovement;
	/** 캐릭터가 느려지는 시간(WebAttack) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spider|Attack", meta=(AllowPrivateAccess=true))
	float WebTime;
	/** WebAttack일시 캐릭터가 일정 시간동안 느려지게 */
	UFUNCTION()
	void WebToPlayerSlow();

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
