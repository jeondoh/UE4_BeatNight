// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemy.generated.h"

UCLASS()
class UE4_BEATNIGHT_API ASpawnEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/**************************************************************************************************/
	// Enemy 스폰

	/** 스폰 타이머 */
	UPROPERTY(meta=(AllowPrivateAccess=true))
	FTimerHandle SpawnTimerHandle;
	/** 스폰 딜레이 시간 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	int32 SpawnDelayTime;
	/** 스폰 타입 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEnemy> SpawnEnemyType;
	/** 스폰시 지정할 몬스터 이름 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	FString SpawnMonsterName;
	/** Enemy 객체 */
	UPROPERTY(VisibleAnywhere, meta=(AllowPrivateAccess=true))
	AEnemy* Enemy;

	UFUNCTION()
	void SpawnEnemyToDelay();

	UFUNCTION()
	void SpawnEnemy();
	
	/**************************************************************************************************/
};
