// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// 초기화
	void InitalizedData();
	
	/**************************************************************************************************/
	// 컴포넌트
	
	/** 어그로 범위 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Component", meta=(AllowPrivateAccess=true))
	class USphereComponent* AgroSphere;
	/** 공격 범위 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Component", meta=(AllowPrivateAccess=true))
	class USphereComponent* AttackSphere;

	/**************************************************************************************************/
	// 몬스터 상태
	
	/** 최대 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Props", meta=(AllowPrivateAccess=true))
	int32 MaxHealth;
	/** 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Props", meta=(AllowPrivateAccess=true))
	int32 Health;
	/** 데미지 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Props", meta=(AllowPrivateAccess=true))
	int32 EnemyDamage;
	/** 스테이지에 따른 몬스터명 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemy|Props", meta=(AllowPrivateAccess=true))
	FString MonsterName;
	
	/**************************************************************************************************/
	// 아이템 드롭

	/** 아이템 드롭 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Items", meta=(AllowPrivateAccess=true))
	bool bDropItem;
	/** 아이템 타입 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Items", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AItem> ItemType;
	/** 아이템 드롭 사운드 */
	UPROPERTY(EditAnywhere, Category = "Enemy|Items", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	class USoundCue* DropSound;
	/** 아이템 드롭 */
	UFUNCTION()
	void DropItem();

	/**************************************************************************************************/
	// 파티클

	/** 공격 받을때 이팩트 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Effect", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* DamagedParticle;

	/** 공격 받을때 사운드 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Effect", meta=(AllowPrivateAccess=true))
	USoundCue* DamagedSound;
	
	/**************************************************************************************************/

// Getter & Setter
public:
	FORCEINLINE FString GetMonsterName() {return MonsterName;}
	FORCEINLINE void SetMonsterName(FString Name) {MonsterName = Name;}
	
};
