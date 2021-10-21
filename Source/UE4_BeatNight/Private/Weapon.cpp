// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "BeatNightPlayer.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// INIT
	WeaponType = EWeaponType::EWT_Sword; // 무기 타입
	WeaponName = EWeaponName::EWN_Noraml; // 무기 이름
	WeaponDamage = 0; // 무기 데미지
	bInInventory = false; // 인벤토리 여부
	WeaponInvenIndex = 0; // 인벤토리 저장 인덱스
	GunAmmo = 0; // 총알 수
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}