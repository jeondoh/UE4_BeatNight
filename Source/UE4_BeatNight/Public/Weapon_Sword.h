// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Engine/DataTable.h"
#include "Weapon_Sword.generated.h"

/**
 * 
 */

// 데이터 테이블 정의 / 무기(Sword) 설정
USTRUCT(BlueprintType)
struct FSwordDataTable : public FTableRowBase
{
	GENERATED_BODY()
	/** Sword 데미지 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponDamage;
	/** Sword Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* StaticMeshDataTable;
	/** Sword Material */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* MatInterface;
	
};

UCLASS()
class UE4_BEATNIGHT_API AWeapon_Sword : public AWeapon
{
	GENERATED_BODY()

public:
	AWeapon_Sword();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	/** 데이터 테이블 세팅 */
	UFUNCTION(BlueprintCallable)
	void SetWeaponDataTable();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetSwordRumble();

private:
	/**************************************************************************************************/
	// 검 속성

	/** 무기(Sword) 등급 속성 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sword|Props", meta=(AllowPrivateAccess=true))
	ESwordType SwordType;

	/** 데이터 테이블 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sword|DataTable", meta=(AllowPrivateAccess=true))
	UDataTable* SwordDataTable;
	
	/** 데이터 테이블 데이터 SET */
	void SetWeaponDataRow(FSwordDataTable* WeaponDataRow);
	
	virtual void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UFUNCTION(BlueprintCallable)
	void DoDamageSword(class AEnemy* Enemy, float Damaged);

	UPROPERTY(EditAnywhere, Category="Sword|Effect", meta=(AllowPrivateAccess=true))
	UParticleSystem* SwordParticle;

	/** 검 공격 타이머 */
	UPROPERTY()
	FTimerHandle SwordTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sword|Timer", meta=(AllowPrivateAccess=true))
	float CollisionEnableTime;
	
	UFUNCTION()
	void DisableCollision();
	
public:
	FORCEINLINE ESwordType GetSwordType() const {return SwordType;}
	FORCEINLINE void SetSwordType(ESwordType Type) {SwordType = Type;}
};
