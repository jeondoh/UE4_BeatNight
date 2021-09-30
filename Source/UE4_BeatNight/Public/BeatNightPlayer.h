// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BeatNightPlayer.generated.h"

UCLASS()
class UE4_BEATNIGHT_API ABeatNightPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABeatNightPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
private:

	void InitalizedData();

	/**************************************************************************************************/
	// 캐릭터 컴포넌트

	UPROPERTY(EditDefaultsOnly, Category="Char|Particle", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* HitUlitmateParticle;

	UPROPERTY(EditDefaultsOnly, Category="Char|Particle", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* HitUlitmateParticle2;
	
	/**************************************************************************************************/
	// 캐릭터 상태
	
	/** HP 최대체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float MaxHealth;

	/** 현재 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float Health;

	/** 캐릭터 방어력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float Defense;

	/** 캐릭터 인벤토리(임시) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Inventory", meta=(AllowPrivateAccess=true))
	TArray<class AWeapon*> Inventory;

	/** 캐릭터 이동속도 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float MovementSpeed;

	void Die();
	
	/**************************************************************************************************/
	// 아이템
	
	/** 코인 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Coins;
	/** 열쇠 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Keys;

	/**************************************************************************************************/
	// VR

	/** VR 왼손 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|VR", meta=(AllowPrivateAccess=true))
	class AMontionActor* LeftController;
	/** VR 오른손 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|VR", meta=(AllowPrivateAccess=true))
	class AMontionActor* RightController;

	/**************************************************************************************************/
	// Enemy 상호작용

	/** Blueprint FireWeapon 이후 적에게 데미지 입힘 */
	UFUNCTION(BlueprintCallable)
	void TraceEnemyToDamage(FVector StartLocation, FVector EndLocation, float WeaponDamage);

	/**************************************************************************************************/


public:
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}
	
	FORCEINLINE float GetHealth() const {return Health;}
	FORCEINLINE void SetHealth(float Amount) {Health = Amount;}
	
	FORCEINLINE uint8 GetItemCoins() const {return Item_Coins;}
	FORCEINLINE void SetItemCoins(int Coins) {Item_Coins = Coins;}

	FORCEINLINE uint8 GetItemKeys() const {return Item_Keys;}
	FORCEINLINE void SetItemKeys(int Keys) {Item_Keys = Keys;}

	FORCEINLINE uint8 GetDefense() const {return Defense;}
	FORCEINLINE void SetDefense(float Amount) {Defense = Amount;}

	FORCEINLINE float GetMovementSpeed() const {return MovementSpeed;}
	FORCEINLINE void SetMovementSpeed(float Speed) {MovementSpeed = Speed;}

	FORCEINLINE TArray<class AWeapon*> GetInventory() const {return Inventory;}

	FORCEINLINE UParticleSystemComponent* GetHitUlitmateParticle() const {return HitUlitmateParticle;}
	FORCEINLINE UParticleSystemComponent* GetHitUlitmateParticle2() const {return HitUlitmateParticle2;}
};
