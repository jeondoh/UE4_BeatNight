// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBullet.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AEnemyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** 총알 생성시 필요 값 Set (Enemy 클래스에서 호출) */
	UFUNCTION()
	void SetBulletInfos(class AEnemy* Enemy, float Speed);

	UFUNCTION()
	void StartCurveBullet();

private:

	/**************************************************************************************************/
	// 컴포넌트
	
	/** Static Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComponent;

	/** Box Comp */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* BoxComponent;

	/** 총알 효과 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Component", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* BulletTrail;

	/**************************************************************************************************/
	// 속성

	/** 총알 속도 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	float BulletSpeed;
	/** 총알 이동 방향 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	FVector Direction;
	/** 속성값이 세팅되었을때 True */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	bool CanMove;
	/** GuidedBullet 소환시 True */
	UPROPERTY(VisibleAnywhere, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	bool CanGuided;
	/** Enemy 클래스 */
	UPROPERTY()
	class AEnemy* Enemy;
	/** 유도탄 커브 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	UCurveFloat* BulletCurve;
	/** Interp 타이머 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	FTimerHandle ItemInerpTimer;
	/** Ulitmate 총알일시 TRUE */
	UPROPERTY(EditAnywhere, Category="Bullet|Props", meta=(AllowPrivateAccess=true))
	bool bUltimateBullet;
	/** BeginPlay시 총알 위치 */
	UPROPERTY()
	FVector BulletLocation;
	/** BeginPlay시 캐릭터 위치 */
	UPROPERTY()
	FVector PlayerLocation;
	/** 유도탄 커브 타이머 시간 */
	UPROPERTY()
	float CurveTime;
	UFUNCTION()
	void GuidedLocation(float DeltaTime);
	UFUNCTION()
	void FinishGuided();
	
	/**************************************************************************************************/
	// 이팩트

	/** 총알 이팩트 (총알이 캐릭터에 맞으면) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* PlayerBulletParticles;
	
	/** 총알 이팩트 (총알이 캐릭터에 맞지 않고 다른 mesh에 맞을때) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* OtherBulletParticles;

	/**************************************************************************************************/
	// 충돌처리

	/** Bullet 충돌처리 */
	UFUNCTION()
	void BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	FTimerHandle DestoryHandler;

	UFUNCTION()
	void DestroyBullet();

	/**************************************************************************************************/
};
