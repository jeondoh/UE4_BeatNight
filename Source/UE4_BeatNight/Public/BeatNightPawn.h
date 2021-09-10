// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BeatNightPawn.generated.h"

UCLASS()
class UE4_BEATNIGHT_API ABeatNightPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABeatNightPawn();

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
	// 캐릭터 상태
	
	/** HP 최대체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float MaxHealth;

	/** 현재 체력 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Char|Props", meta=(AllowPrivateAccess=true))
	float Health;

	void Die();

};
