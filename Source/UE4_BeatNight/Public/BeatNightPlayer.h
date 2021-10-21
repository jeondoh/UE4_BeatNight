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

	void LoadGame();

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

	/** 캐릭터 인벤토리 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Inventory", meta=(AllowPrivateAccess=true))
	TArray<class AWeapon*> Inventory;

	/** 캐릭터 인벤토리 Class */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Inventory", meta=(AllowPrivateAccess=true))
	class AInventory* BPInventory;

	/** 캐릭터 이동속도 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float MovementSpeed;

	/** 스테이지 정보 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Props", meta=(AllowPrivateAccess=true))
	FName PlayerStageName;

	/** Stage1 클리어 이후 이동가능여부 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Props", meta=(AllowPrivateAccess=true))
	bool bCanGoStage2;

	void Die();
	
	/**************************************************************************************************/
	// 아이템
	
	/** 코인 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Coins;
	/** 열쇠(가챠박스) */
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
	/** VR Widget Interaction */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Char|VR", meta = (AllowPrivateAccess = true))
	class UWidgetInteractionComponent* WidgetComp;
	/** 인벤토리 장착 여부 확인(Overlap 되었을때) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Inventory", meta=(AllowPrivateAccess=true))
	bool bCanInventory;
	/** 인벤토리 인덱스(Overlap 되었을때) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Inventory", meta=(AllowPrivateAccess=true))
	int InventoryIndex;
	/** 인벤토리 확인 */
	UFUNCTION(BlueprintCallable)
	bool CheckInventory(int Index);
	/** Inventory에 무기 저장 */
	UFUNCTION(BlueprintCallable)
	bool AddInventory(class AWeapon* AttachWeapon);
	/** Inventory에서 무기 제거 */
	UFUNCTION(BlueprintCallable)
	void RemoveInventory(int Index);

	/**************************************************************************************************/
	// Enemy 상호작용

	/** Blueprint FireWeapon 이후 적에게 데미지 입힘 */
	UFUNCTION(BlueprintCallable)
	void TraceEnemyToDamage(FVector StartLocation, FVector EndLocation, float WeaponDamage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Effect", meta=(AllowPrivateAccess=true))
	UParticleSystem* GunParticle;
	
	/**************************************************************************************************/


public:
	FORCEINLINE float GetMaxHealth() const {return MaxHealth;}

	FORCEINLINE FName GetPlayerStageName() const {return PlayerStageName;}
	FORCEINLINE void SetPlayerStageName(FName Name) {PlayerStageName = Name;}
	
	FORCEINLINE float GetHealth() const {return Health;}
	FORCEINLINE void SetHealth(float Amount) {Health = Amount;}

	FORCEINLINE bool GetCanGoStage2() const {return bCanGoStage2;}
	FORCEINLINE void SetCanGoStage2(bool Cango) {bCanGoStage2 = Cango;}
	
	FORCEINLINE uint8 GetItemCoins() const {return Item_Coins;}
	FORCEINLINE void SetItemCoins(int Coins) {Item_Coins = Coins;}

	FORCEINLINE uint8 GetItemKeys() const {return Item_Keys;}
	FORCEINLINE void SetItemKeys(int Keys) {Item_Keys = Keys;}

	FORCEINLINE uint8 GetDefense() const {return Defense;}
	FORCEINLINE void SetDefense(float Amount) {Defense = Amount;}

	FORCEINLINE float GetMovementSpeed() const {return MovementSpeed;}
	FORCEINLINE void SetMovementSpeed(float Speed) {MovementSpeed = Speed;}

	FORCEINLINE TArray<class AWeapon*> GetInventory() const {return Inventory;}
	FORCEINLINE void SetInventory(TArray<class AWeapon*> WeaponArr) {Inventory = WeaponArr;}

	FORCEINLINE UParticleSystemComponent* GetHitUlitmateParticle() const {return HitUlitmateParticle;}
	FORCEINLINE UParticleSystemComponent* GetHitUlitmateParticle2() const {return HitUlitmateParticle2;}
};
