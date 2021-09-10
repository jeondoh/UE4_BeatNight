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
	void SetBulletInfos(FVector Location, float Speed);

private:

	/**************************************************************************************************/
	// 컴포넌트
	
	/** Static Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComponent;

	/** Box Comp */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* BoxComponent;

	/**************************************************************************************************/
	// 속성

	/** 총알 속도 */
	UPROPERTY()
	float BulletSpeed;
	/** 총알 생성시간 기준 플레이어 위치 */
	UPROPERTY()
	FVector PlayerLocation;
	/** 속성값이 세팅되었을때 True */
	UPROPERTY()
	bool CanMove;
	
	/**************************************************************************************************/
	// 이팩트

	/** 총알 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Bullet|Particles", meta = (AllowPrivateAccess=true))
	class UParticleSystem* BulletParticles;

	/**************************************************************************************************/
	// 충돌처리

	/** Bullet 충돌처리 */
	UFUNCTION()
	void BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**************************************************************************************************/

};
