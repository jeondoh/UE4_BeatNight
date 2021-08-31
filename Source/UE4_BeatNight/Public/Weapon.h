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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/**************************************************************************************************/
	// 무기 속성
	
	/** 무기 열거형 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Type", meta=(AllowPrivateAccess=true))
	EWeaponType WeaponType;

	/** 무기 데미지 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	int32 WeaponDamage;

	/** 무기(총) 총알 수 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	int32 GunAmmo;

	/**************************************************************************************************/
	// 무기 효과

	/** 무기 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	class UParticleSystem* WeaponEffect;

	/** 무기 사운드  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Props", meta=(AllowPrivateAccess=true))
	class USoundCue* WeaponSound;

	/**************************************************************************************************/
};
