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

	/** 비헤이비어 설정 (SpawnEnemy에서 호출함) */
	void SetEnemyAIController();

	/** Enemy 컨트롤러 */
	UPROPERTY()
	class AEnemyAIController* EnemyController;

	/** 데미지 입히기 */
	UFUNCTION()
	void DoDamage(class ABeatNightPlayer* Player);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 캐릭터(Player)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Enemy", meta=(AllowPrivateAccess=true))	
	class ABeatNightPlayer* BeatNightPlayer;

	/**************************************************************************************************/
	// 애니메이션 & 몽타주

	/** 공격 몽타주 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Anim", meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;

	/** HP x% 이하일때 공격 몽타주 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Anim", meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackHpDwonMontage;

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
	/** 공격가능여부(AnimInstance에서 사용) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemy|Props", meta=(AllowPrivateAccess=true))
	bool bCanAttack;
	/** 공격 전 딜레이 시간 (각 섹션마다 대기시간 다름) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Boss|Props", meta=(AllowPrivateAccess=true))
	float DelayTime;

	/**************************************************************************************************/
	
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
	// 인공지능

	/** Enemy의 행동 AI */
	UPROPERTY(EditAnywhere, Category="Enemy|BehaviorTree", meta=(AllowPrivateAccess=true))
	class UBehaviorTree* BehaviorTree;
	/** 적이 이동할 지점
	 * MakeEditWidget = 해당 엑터의 위치를 중심으로 한 로컬 위치
	 */
	UPROPERTY(VisibleAnywhere, Category="Enemy|BehaviorTree", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	FVector PatrolPoint;
	UPROPERTY(VisibleAnywhere, Category="Enemy|BehaviorTree", meta=(AllowPrivateAccess=true, MakeEditWidget=true))
	FVector PatrolPoint2;
	/** 어그로 범위 오버랩 */
	UFUNCTION()
	void AgroSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void AgroSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	/** 공격 범위 오버랩 */
	UFUNCTION()
	void AttackSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttackSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Player 방향 바라보게 하기 */
	UFUNCTION(BlueprintCallable)
	void GetLookAtRotation(FVector TargetLocation);

	float RandomizationDamage(float Damage);
	
	/**************************************************************************************************/

// Getter & Setter
public:
	FORCEINLINE FString GetMonsterName() const {return MonsterName;}
	FORCEINLINE void SetMonsterName(FString Name) {MonsterName = Name;}

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const {return BehaviorTree;}

	FORCEINLINE void SetPatrolPoint(FVector PT) {PatrolPoint = PT;}
	FORCEINLINE void SetPatrolPoint2(FVector PT) {PatrolPoint2 = PT;}

	FORCEINLINE bool GetCanAttack() const {return bCanAttack;}
	FORCEINLINE void SetCanAttack(bool bAttack) {bCanAttack = bAttack;}

	FORCEINLINE float GetEnemyDamage() const {return EnemyDamage;}
	FORCEINLINE void SetEnemyDamage(float Damage) {EnemyDamage = Damage;}
	
};
