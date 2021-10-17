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
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetLoadInventoryToPlayer(class ABeatNightPlayer* Player);
	
private:

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	class UBeatNightSaveGame* LoadGameInstance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TArray<class AWeapon*> LoadPlayerInventory;
	
	UFUNCTION()
	void SaveInventory(class UBeatNightSaveGame* GameInstance, class ABeatNightPlayer* Player);

	UFUNCTION()
	void LoadInventory(ABeatNightPlayer* Player);
};
