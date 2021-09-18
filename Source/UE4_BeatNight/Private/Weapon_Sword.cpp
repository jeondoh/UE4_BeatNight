// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Sword.h"

AWeapon_Sword::AWeapon_Sword()
{
}

void AWeapon_Sword::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetWeaponDataTable();
}

void AWeapon_Sword::SetWeaponDataTable()
{
	const FString WeaponTablePath{TEXT("DataTable'/Game/00_BeatNight/Weapons/Swords/SwordDataTable.SwordDataTable'")};
	UDataTable* WeaponTableObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *WeaponTablePath));
	
	if (WeaponTableObject)
	{
		FSwordDataTable* WeaponDataRow = nullptr;
		switch (SwordType)
		{
		case ESwordType::EST_Level1:
			WeaponDataRow = WeaponTableObject->FindRow<FSwordDataTable>(FName("LEVEL1"), TEXT(""));			
			break;
		case ESwordType::EST_Level2:
			WeaponDataRow = WeaponTableObject->FindRow<FSwordDataTable>(FName("LEVEL2"), TEXT(""));			
			break;
		case ESwordType::EST_Level3:
			WeaponDataRow = WeaponTableObject->FindRow<FSwordDataTable>(FName("LEVEL3"), TEXT(""));			
			break;
		case ESwordType::EST_Level4:
			WeaponDataRow = WeaponTableObject->FindRow<FSwordDataTable>(FName("LEVEL4"), TEXT(""));			
			break;
		}
		SetWeaponDataRow(WeaponDataRow);
	}
}

void AWeapon_Sword::SetWeaponDataRow(FSwordDataTable* WeaponDataRow)
{
	if(WeaponDataRow)
	{
		WeaponDamage = WeaponDataRow->WeaponDamage;
		StaticMeshComponent->SetStaticMesh(WeaponDataRow->StaticMeshDataTable);
		StaticMeshComponent->SetMaterial(0, WeaponDataRow->MatInterface);
	}
}
