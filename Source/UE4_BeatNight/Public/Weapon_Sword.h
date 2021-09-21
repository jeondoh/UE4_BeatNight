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

public:
	FORCEINLINE ESwordType GetSwordType() const {return SwordType;}
	FORCEINLINE void SetSwordType(ESwordType Type) {SwordType = Type;}
};
