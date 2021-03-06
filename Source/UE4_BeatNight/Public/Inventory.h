// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** 인벤토리 슬롯 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	USceneComponent* RootSceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory|", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* Slot6;

	/** MontionController에 닿이면 보여짐 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory|Comp", meta=(AllowPrivateAccess=true))
	class UBoxComponent* CollisionBox;

	/** Player Class > Blueprint에서 초기화 해줌 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory|Props", meta=(AllowPrivateAccess=true))
	class ABeatNightPlayer* InventoryPlayer;
	
	/** 슬롯 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory|", meta=(AllowPrivateAccess=true))
	TArray<UStaticMeshComponent*> SlotMeshArr;

};
