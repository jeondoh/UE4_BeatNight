// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "WeaponType.h"
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
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame|Data")
	TArray<int32> WeaponIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame|Data")
	TArray<int32> WeaponAmmo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame|Data")
	TArray<EWeaponType> WeaponTypeArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame|Data")
	TArray<EWeaponName> WeaponNameArr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame|Data")
	TArray<ESwordType> WeaponSwordLevelArr;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="SaveGame")
	FWeaponData WeaponData;
	
};
