// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemType.h"
#include "Engine/StaticMeshActor.h"
#include "Item.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**************************************************************************************************/
	// 컴포넌트

	/** 스테틱 메시 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props")
	class UStaticMeshComponent* StaticMeshComponent;

	/** 충돌상자 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	class UBoxComponent* CollisionBox;

	/** 아이템 범위 Collision */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	class USphereComponent* AreaSphere;

	/**************************************************************************************************/
	// 아이템 속성 

	/** 아이템 외형 파티클 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemComp|Props")
	class UParticleSystem* ItemParticle;
	
	/** 아이템 회전 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemComp|Rotate")
	bool BItemRotate;

	/** 아이템 회전 속도 */
	UPROPERTY(EditAnywhere, Category="ItemComp|Rotate")
	int32 RotateSpeed;

	/** 아이템 정보 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemComp|Props")
	EItemType ItemType;

	/** 아이템을 사기 위한 코인 개수 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props")
	uint8 ItemCoin;

	/** 플레이어 */
	UPROPERTY()
	class ABeatNightPlayer* CastPlayer;

	UFUNCTION(BlueprintCallable)
	bool BuyItem();

	/** 아이템 회전 여부에 따라 회전 */
	void ItemRotate(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** BoxCollision 오버랩 */
	UFUNCTION()
	virtual void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/** AreaSphere범위 오버랩 */
	UFUNCTION()
	virtual void AreaSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void AreaSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE	uint8 GetItemCoin() const {return ItemCoin;}
};
