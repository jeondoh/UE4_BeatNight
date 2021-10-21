// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotalActor.generated.h"

UCLASS()
class UE4_BEATNIGHT_API APotalActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotalActor();

	/** 레벨 클리어시 문 열림 */
	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();
	
	/** 레벨 시퀀스 실행 */
	UFUNCTION(BlueprintImplementableEvent)
	void PlayLevelSeq(class ABeatNightPlayer* Player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	USceneComponent* DefaultSceneComponent;
	/** Static Mesh */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComponent;
	/** Box Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* BoxComponent;
	/** Arrow Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UArrowComponent* Arrow;
	/** 순간이동 위치 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FVector MoveToLocation;
	/** 이동여부 */
	UPROPERTY(EditAnywhere, Category="Potal", BlueprintReadWrite, meta=(AllowPrivateAccess=true))
	bool bCanMove;
	/** 태그명 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potal", meta=(AllowPrivateAccess=true))
	FName TagName;
	
	UFUNCTION()
	void BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FORCEINLINE void SetbCanMove(bool bMove) {bCanMove = bMove;}
};
