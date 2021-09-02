// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightPawn.h"

#include "Components/SphereComponent.h"

// Sets default values
ABeatNightPawn::ABeatNightPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Comp = CreateDefaultSubobject<USphereComponent>(TEXT("asdffdsa"));
}

// Called when the game starts or when spawned
void ABeatNightPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeatNightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABeatNightPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

