// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BeatNightSaveGame.generated.h"


// 저장 데이터
USTRUCT(BlueprintType)
struct FBeatNightData
{
	GENERATED_BODY()

	/** 캐릭터 체력 */
	UPROPERTY(VisibleAnywhere, Category="SaveGame|Data")
	float Health;
	/** 캐릭터 방어력 */
	UPROPERTY(VisibleAnywhere, Category="SaveGame|Data")
	float Defense;
	/** 코인 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Coins;
	/** 열쇠(가챠박스) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Keys;
	/** 인벤토리 정보 */
	UPROPERTY(VisibleAnywhere, Category="SaveGame|Data")
	TArray<class AWeapon*> Inventory;
};

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API UBeatNightSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UBeatNightSaveGame();

	UPROPERTY(VisibleAnywhere, Category="SaveGame")
	FString PlayerName;
	
	UPROPERTY(VisibleAnywhere, Category="SaveGame")
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category="SaveGame")
	FBeatNightData BeatNightData;
	
};
