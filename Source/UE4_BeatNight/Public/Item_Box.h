// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Item_Box.generated.h"

/**
 * 
 */
UCLASS()
class UE4_BEATNIGHT_API AItem_Box : public AItem
{
	GENERATED_BODY()

public:
	AItem_Box();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gacha", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AItem> GachaItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Gacha", meta=(AllowPrivateAccess=true))
	FVector SpawnLocation;
};
