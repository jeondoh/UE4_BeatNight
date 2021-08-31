// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	/**************************************************************************************************/
	// 컴포넌트

	/** 아이템 메시 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* ItemMesh;

	/** 충돌상자 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	class UBoxComponent* CollisionBox;

	/** 아이템 범위 Collision */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	class USphereComponent* AreaSphere;

	/**************************************************************************************************/
	// 아이템 속성 

	/** 아이템 외형 파티클 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemComp|Props", meta=(AllowPrivateAccess=true))
	class UParticleSystem* ItemParticle;
	
	/** 아이템 회전 여부 */
	UPROPERTY(EditAnywhere, Category="ItemComp|Rotate", meta=(AllowPrivateAccess=true))
	bool BItemRotate;

	/** 아이템 회전 속도 */
	UPROPERTY(EditAnywhere, Category="ItemComp|Rotate", meta=(AllowPrivateAccess=true))
	int32 RotateSpeed;

	/** 아이템 회전 여부에 따라 회전 */
	void ItemRotate(float DeltaTime);

	/**************************************************************************************************/
};
