// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "SpawnSpiderEnemy.generated.h"

UCLASS()
class UE4_BEATNIGHT_API ASpawnSpiderEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnSpiderEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/** 죽을때 드롭여부 */
	UPROPERTY(EditAnywhere, Category="EnemySpawn|Drop", meta=(AllowPrivateAccess=true))
	bool bDropItem;
	/** 아이템 타입 */
	UPROPERTY(EditAnywhere, Category="EnemySpawn|Drop", meta=(AllowPrivateAccess=true))
	TSubclassOf<AItem> ItemType;
	
	UFUNCTION()
	void SpawnEnemy();

private:
	/**************************************************************************************************/
	// BossStage1 Spider Enemy 스폰
	
	/** 스폰 타입 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	TSubclassOf<class ASpider> SpawnEnemyType;
	/** 스폰시 지정할 몬스터 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	FName SpawnMonsterName;

	/**************************************************************************************************/

};
