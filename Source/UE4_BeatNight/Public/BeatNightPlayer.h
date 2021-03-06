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

	/** 데미지(Enemy) UI */
	UFUNCTION(BlueprintImplementableEvent)
	void ShowHitNumber(int32 Damage, FVector HitLocation, FRotator HitRotator);
	/** 데미지(Player) UI */
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDamagedUI();
	/** 사망시 UI */
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDieWidget();
	/** 상점 > 아이템 구매 */
	UFUNCTION(BlueprintCallable)
	void BuyItem(class AItem* Item, FName ItemName);
	/** 아이템 획득(Key, Coin) */
	UFUNCTION(BlueprintImplementableEvent)
	void ShowGetItemUI();
	/** 상점 > 아이템 구매 실패 */
	UFUNCTION(BlueprintImplementableEvent)
	void GetFailItemToShop();
	/** 상점 > 아이템 업그레이드 실패 */
	UFUNCTION(BlueprintImplementableEvent)
	void GetFailItemToUpgrade();
	/** 게임 클리어 위젯 */
	UFUNCTION(BlueprintImplementableEvent)
	void ShowGameClearWidget();
	
private:

	void InitalizedData();

	void LoadGame();

	/**************************************************************************************************/
	// 캐릭터 컴포넌트

	UPROPERTY(EditDefaultsOnly, Category="Char|Particle", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* HitUlitmateParticle;

	UPROPERTY(EditDefaultsOnly, Category="Char|Particle", meta=(AllowPrivateAccess=true))
	UParticleSystemComponent* HitUlitmateParticle2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Component", meta=(AllowPrivateAccess=true))
	class UWidgetComponent* HitWidget;
	
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

	/** 캐릭터 사망 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Props", meta=(AllowPrivateAccess=true))
	bool bPlayerDie;

	/** 게임 클리어 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Props", meta=(AllowPrivateAccess=true))
	bool bGameClear;
	
	/** 캐릭터 사망 */
	UPROPERTY(BlueprintReadOnly, Category="Char|Props", meta=(AllowPrivateAccess=true))
	FName GetItemName;

	void Die();
	
	/**************************************************************************************************/
	// 아이템
	
	/** 코인 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Coins;
	/** 열쇠(가챠박스) */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|Items", meta=(AllowPrivateAccess=true))
	uint8 Item_Keys;

	/**************************************************************************************************/
	// VR

	/** VR 왼손 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|VR", meta=(AllowPrivateAccess=true))
	class AMontionActor* LeftController;

	/** VR 오른손 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Char|VR", meta=(AllowPrivateAccess=true))
	class AMontionActor* RightController;
	
	/** VR Widget Interaction 왼손*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Char|VR", meta = (AllowPrivateAccess = true))
	class UWidgetInteractionComponent* WidgetCompLeft;
	/** VR Widget Interaction 오른손*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Char|VR", meta = (AllowPrivateAccess = true))
	class UWidgetInteractionComponent* WidgetCompRight;
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
	/** 데미지 랜덤화 */
	UFUNCTION()
	float RandomizationDamage(float Damage);

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

	FORCEINLINE void SetItemName(FName TEXT) {GetItemName = TEXT;}

	FORCEINLINE FName GetPlayerStageName() const {return PlayerStageName;}
	FORCEINLINE void SetPlayerStageName(FName Name) {PlayerStageName = Name;}
	
	FORCEINLINE float GetHealth() const {return Health;}
	FORCEINLINE void SetHealth(float Amount) {Health = Amount;}

	FORCEINLINE bool GetCanGoStage2() const {return bCanGoStage2;}
	FORCEINLINE void SetCanGoStage2(bool Cango) {bCanGoStage2 = Cango;}

	FORCEINLINE void SetGameClear(bool Clear) {bGameClear = Clear;}
	
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

