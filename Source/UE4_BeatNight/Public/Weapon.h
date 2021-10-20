// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "WeaponType.h"
#include "Weapon.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AWeapon : public AItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/**************************************************************************************************/
	// 무기 속성
	
	/** 무기 종류 열거형 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Type")
	EWeaponType WeaponType;
	
	/** 무기 이름 열거형 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Type")
	EWeaponName WeaponName;

	/** 무기 데미지 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props")
	int32 WeaponDamage;

	/** 무기(총) 총알 수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props")
	int32 GunAmmo;

	/** 무기 사운드  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	class USoundCue* WeaponSound;
	
	/**************************************************************************************************/

private:
	/**************************************************************************************************/
	// 무기 효과

	/** 무기 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	class UParticleSystem* WeaponEffect;

	/**************************************************************************************************/
	// 인벤토리

	/** 무기가 인벤토리에 있는지 여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon|Inventory", meta=(AllowPrivateAccess=true))
	bool bInInventory;
	/** 인벤토리에 저장되어 있는 인덱스 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon|Inventory", meta=(AllowPrivateAccess=true))
	int WeaponInvenIndex;
	
	/**************************************************************************************************/

public:
	FORCEINLINE EWeaponType GetEWeaponType() const {return WeaponType;}
	FORCEINLINE void SetEWeaponType(EWeaponType Type) { WeaponType = Type;}
	FORCEINLINE EWeaponName GetEWeaponName() const {return WeaponName;}
	FORCEINLINE void SetEWeaponName(EWeaponName Name) { WeaponName = Name;}
	FORCEINLINE int32 GetGunAmmo() const {return GunAmmo;}
	FORCEINLINE void SetGunAmmo(int32 Ammo) { GunAmmo = Ammo;}
	
};
