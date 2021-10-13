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

	/** 슬롯 배열 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Inventory|", meta=(AllowPrivateAccess=true))
	TArray<UStaticMeshComponent*> SlotMeshArr;

	/** 오버랩 이벤트 */
	UFUNCTION()
	void OverlapBeginSlot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OverlapEndSlot(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
