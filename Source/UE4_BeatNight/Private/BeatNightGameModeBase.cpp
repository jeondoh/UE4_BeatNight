// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightGameModeBase.h"

#include "BeatNightPlayer.h"
#include "BeatNightSaveGame.h"
#include "Weapon.h"
#include "Weapon_Sword.h"
#include "Kismet/GameplayStatics.h"

ABeatNightGameModeBase::ABeatNightGameModeBase()
{
}

void ABeatNightGameModeBase::SaveGame()
{
	UBeatNightSaveGame* GameInstance = Cast<UBeatNightSaveGame>(UGameplayStatics::CreateSaveGameObject(UBeatNightSaveGame::StaticClass()));
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));

	GameInstance->BeatNightData.Health = Player->GetHealth();
	GameInstance->BeatNightData.Defense = Player->GetDefense();
	GameInstance->BeatNightData.Item_Coins = Player->GetItemCoins();
	GameInstance->BeatNightData.Item_Keys = Player->GetItemKeys();
	SaveInventory(GameInstance, Player);

	UGameplayStatics::SaveGameToSlot(GameInstance, GameInstance->PlayerName, GameInstance->UserIndex);
}

void ABeatNightGameModeBase::LoadGame()
{
	const UBeatNightSaveGame* GameInstance = Cast<UBeatNightSaveGame>(UGameplayStatics::CreateSaveGameObject(UBeatNightSaveGame::StaticClass()));
	LoadGameInstance = Cast<UBeatNightSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->PlayerName, GameInstance->UserIndex));
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	if(LoadGameInstance)
	{
		Player->SetHealth(LoadGameInstance->BeatNightData.Health);
		Player->SetDefense(LoadGameInstance->BeatNightData.Defense);
		Player->SetItemCoins(LoadGameInstance->BeatNightData.Item_Coins);
		Player->SetItemKeys(LoadGameInstance->BeatNightData.Item_Keys);
		SetLoadInventoryToPlayer(Player);
		// LoadInventory(LoadGameInstance, Player);
	}
}

void ABeatNightGameModeBase::SaveInventory(UBeatNightSaveGame* GameInstance, ABeatNightPlayer* Player)
{
	int Index = -1;
	TArray<AWeapon*> PlayerInventory = Player->GetInventory();
	for(AWeapon* Weapon : PlayerInventory)
	{
		Index++;
		if(Weapon == nullptr) continue;
		GameInstance->WeaponData.WeaponIndex.Add(Index);
		GameInstance->WeaponData.WeaponAmmo.Add(Weapon->GetGunAmmo());
		GameInstance->WeaponData.WeaponNameArr.Add(Weapon->GetEWeaponName());
	
		EWeaponType Type = Weapon->GetEWeaponType();
		GameInstance->WeaponData.WeaponTypeArr.Add(Type);
		// Weapon 타입이 Sword일 경우 Sword LEVEL 저장
		if(Type == EWeaponType::EWT_Sword)
		{
			AWeapon_Sword* Sword = Cast<AWeapon_Sword>(Weapon);
			if(Sword)
			{
				ESwordType GetType = Sword->GetSwordType();
				GameInstance->WeaponData.WeaponSwordLevelArr.Add(GetType);
			}
		}
	}
}

void ABeatNightGameModeBase::LoadInventory(ABeatNightPlayer* Player)
{
	if(LoadGameInstance)
	{
		SetLoadInventoryToPlayer(Player);
		/*
		int SwordIndex = 0;
		LoadPlayerInventory.Init(nullptr, 6);
		// Player Inventory 초기화
		TArray<int32> LoadArr = LoadGameInstance->WeaponData.WeaponIndex; // Inventory Index값
		TArray<int32> LoadWeaponAmmo = LoadGameInstance->WeaponData.WeaponAmmo; // Weapon 총알수
		TArray<EWeaponType> LoadWeaponType = LoadGameInstance->WeaponData.WeaponTypeArr; // Weapon 타입
		TArray<EWeaponName> LoadWeaponName = LoadGameInstance->WeaponData.WeaponNameArr; // Weapon 이름
		TArray<ESwordType> LoadSwordLevelArr = LoadGameInstance->WeaponData.WeaponSwordLevelArr; // Weapon(Sword) 레벨
		
		for(int i=0; i<LoadWeaponType.Num(); i++)
		{
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			
			if(LoadWeaponType[i] == EWeaponType::EWT_Sword)
			{
				AWeapon_Sword* Sword = GetWorld()->SpawnActor<AWeapon_Sword>(AWeapon_Sword::StaticClass(), Param);
				if(Sword)
				{
					Sword->SetEWeaponType(LoadWeaponType[i]);
					Sword->SetSwordType(LoadSwordLevelArr[SwordIndex++]);
					Sword->SetWeaponDataTable();
					LoadPlayerInventory[LoadArr[i]] = Sword;					
				}
			}
			else
			{
				AWeapon* LoadWeapon = GetWorld()->SpawnActor<AWeapon>(AWeapon::StaticClass(), Param);
				LoadWeapon->SetGunAmmo(LoadWeaponAmmo[i]);
				LoadWeapon->SetEWeaponType(LoadWeaponType[i]);
				LoadWeapon->SetEWeaponName(LoadWeaponName[i]);
				LoadPlayerInventory[LoadArr[i]] = LoadWeapon;	
			}
		}
		Player->SetInventory(LoadPlayerInventory);
		// SetLoadInventoryToPlayer();
		*/
	}
}
