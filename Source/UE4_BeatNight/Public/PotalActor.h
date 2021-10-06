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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Static Mesh */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComponent;
	/** Box Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* BoxComponent;
	/** Arrow Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UArrowComponent* Arrow;
	/** 포탈 파티클 Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UParticleSystemComponent* PortalParticle;
	/** 순간이동 위치 */
	UPROPERTY()
	FVector MoveToLocation;
	/** 이동여부 */
	UPROPERTY()
	bool bCanMove;
	/** 태그명 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Potal", meta=(AllowPrivateAccess=true))
	FName TagName;
	
	UFUNCTION()
	void BoxCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BoxCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE class UParticleSystemComponent* GetPortalParticle() const {return PortalParticle;}
	FORCEINLINE void SetbCanMove(bool bMove) {bCanMove = bMove;}
};
