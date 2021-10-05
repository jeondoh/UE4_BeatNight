// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageDivActor.generated.h"

UCLASS()
class UE4_BEATNIGHT_API AStageDivActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStageDivActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	/**************************************************************************************************/
	// 컴포넌트
	
	/** Static Mesh */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	UStaticMeshComponent* StaticMeshComponent;

	/** Box Comp */
	UPROPERTY(VisibleAnywhere, Category="Component", meta=(AllowPrivateAccess=true))
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/**************************************************************************************************/
	// 기능

	/** 스테이지 구분 */
	UPROPERTY(EditAnywhere, Category="Stage", meta=(AllowPrivateAccess=true))
	FName StageName;

	/**************************************************************************************************/
};
