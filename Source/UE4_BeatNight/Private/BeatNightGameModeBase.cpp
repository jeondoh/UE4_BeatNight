// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightGameModeBase.h"

#include "BeatNightPlayer.h"
#include "BeatNightSaveGame.h"
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
	UBeatNightSaveGame* GameInstance = Cast<UBeatNightSaveGame>(UGameplayStatics::CreateSaveGameObject(UBeatNightSaveGame::StaticClass()));
	UBeatNightSaveGame* LoadGameInstance = Cast<UBeatNightSaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->PlayerName, GameInstance->UserIndex));
	ABeatNightPlayer* Player = Cast<ABeatNightPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	if(LoadGameInstance)
	{
		Player->SetHealth(LoadGameInstance->BeatNightData.Health);
		Player->SetDefense(LoadGameInstance->BeatNightData.Defense);
		Player->SetItemCoins(LoadGameInstance->BeatNightData.Item_Coins);
		Player->SetItemKeys(LoadGameInstance->BeatNightData.Item_Keys);
		LoadInventory(LoadGameInstance, Player);
	}
}

void ABeatNightGameModeBase::SaveInventory(UBeatNightSaveGame* GameInstance, ABeatNightPlayer* Player)
{
	TArray<AWeapon*> PlayerInventory = Player->GetInventory();
	for(AWeapon* Weapon : PlayerInventory)
	{
		GameInstance->BeatNightData.Inventory.Add(Weapon);
	}
}

void ABeatNightGameModeBase::LoadInventory(UBeatNightSaveGame* LoadGameInstance, ABeatNightPlayer* Player)
{
	TArray<AWeapon*> LoadInventory = LoadGameInstance->BeatNightData.Inventory;
	for(AWeapon* Weapon : LoadInventory)
	{
		Player->GetInventory().Add(Weapon);
	}
}