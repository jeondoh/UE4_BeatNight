// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Sword.h"

#include "BeatNightPlayer.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AWeapon_Sword::AWeapon_Sword()
{
	CollisionEnableTime = 1.f;
}

void AWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();
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

void AWeapon_Sword::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == nullptr) return;

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if(Enemy)
	{
		if(Enemy->GetDying()) return;
		const int RandomDamaged = RandomizationDamage(WeaponDamage);
		DoDamageSword(Enemy, RandomDamaged);
		const FTransform SocketTransform = StaticMeshComponent->GetSocketTransform("HitSocket", ERelativeTransformSpace::RTS_World);
		if(SwordParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SwordParticle, SocketTransform.GetLocation());
			// 데미지 UI 보여주기
			Enemy->ShowHitNumber(RandomDamaged, SocketTransform.GetLocation());
		}
		if(WeaponSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, WeaponSound, SocketTransform.GetLocation());
		}
		
	}
}

void AWeapon_Sword::DoDamageSword(AEnemy* Enemy, float Damaged)
{
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	UGameplayStatics::ApplyDamage(Enemy, Damaged, Player->GetController(), this, UDamageType::StaticClass());
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetSwordRumble();
	GetWorldTimerManager().SetTimer(SwordTimer, this, &AWeapon_Sword::DisableCollision, CollisionEnableTime);
}

void AWeapon_Sword::DisableCollision()
{
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
