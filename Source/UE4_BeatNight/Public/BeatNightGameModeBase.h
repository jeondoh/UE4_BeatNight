// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BeatNightGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API ABeatNightGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABeatNightGameModeBase();

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
	
private:
	UFUNCTION()
	void SaveInventory(class UBeatNightSaveGame* GameInstance, class ABeatNightPlayer* Player);
	UFUNCTION()
	void LoadInventory(class UBeatNightSaveGame* LoadGameInstance, class ABeatNightPlayer* Player);

};
