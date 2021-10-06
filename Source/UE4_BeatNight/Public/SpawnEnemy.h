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
	UFUNCTION()
	void SpawnEnemy();

private:
	/** 태그명 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	FName TagName;
	
	/**************************************************************************************************/
	// Enemy 스폰

	/** 스폰 타입 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AEnemy> SpawnEnemyType;
	/** 스폰시 지정할 몬스터.명 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="EnemySpawn", meta=(AllowPrivateAccess=true))
	FName SpawnMonsterName;
	/** 적이 이동할 지점
	* MakeEditWidget = 해당 엑터의 위치를 중심으로 한 로컬 위치
	*/
	UPROPERTY(EditAnywhere, Category="EnemySpawn", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	FVector PatrolPoint;
	UPROPERTY(EditAnywhere, Category="EnemySpawn", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	FVector PatrolPoint2;

	/**************************************************************************************************/
};
