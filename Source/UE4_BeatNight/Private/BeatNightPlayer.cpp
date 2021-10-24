// Fill out your copyright notice in the Description page of Project Settings.


#include "BeatNightPlayer.h"

#include "BeatNightGameModeBase.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "EnemyAIController.h"
#include "Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ABeatNightPlayer::ABeatNightPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitalizedData(); // 초기화

	HitUlitmateParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitUlitmateParticle"));
	HitUlitmateParticle2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("HitUlitmateParticle2"));
	HitWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HitWidget"));

	HitUlitmateParticle->SetupAttachment(GetRootComponent());
	HitUlitmateParticle2->SetupAttachment(GetRootComponent());

	HitUlitmateParticle->SetVisibility(false);
	HitUlitmateParticle2->SetVisibility(false);

	bCanInventory = false;
	bPlayerDie = false;
}

// Called when the game starts or when spawned
void ABeatNightPlayer::BeginPlay()
{
	Super::BeginPlay();
	Inventory.Init(nullptr, 6);
	LoadGame();
}

// Called every frame
void ABeatNightPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABeatNightPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABeatNightPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Defense >= DamageAmount ? 0 : DamageAmount - Defense;
	Health -= DamageAmount;
	if(Health <= 0.f)
	{
		Health = 0.f;
		Die();

		auto EnemyController = Cast<AEnemyAIController>(EventInstigator);
		if(EnemyController)
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(TEXT("PlayerDeath"), true);			
		}
		return 0;
	}
	ShowDamagedUI();
	return DamageAmount;
}

void ABeatNightPlayer::InitalizedData()
{
	MaxHealth = 1000.f;
	Health = 1000.f;
	MovementSpeed = 1.f;
	bCanGoStage2 = false;
}

void ABeatNightPlayer::LoadGame()
{
	ABeatNightGameModeBase* GameMode = Cast<ABeatNightGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->LoadGame();
}

void ABeatNightPlayer::Die()
{
	SetMovementSpeed(0.f);
	bPlayerDie = true;
	ShowDieWidget();
}

bool ABeatNightPlayer::CheckInventory(int Index)
{
	if(Inventory[Index] == nullptr)
	{
		InventoryIndex = Index;
		return true;
	}
	return false;
}

bool ABeatNightPlayer::AddInventory(AWeapon* AttachWeapon)
{
	if(InventoryIndex == -1) return false;
	if(bCanInventory && AttachWeapon)
	{
		Inventory[InventoryIndex] = AttachWeapon;
		return true;
	}
	return false;
}

void ABeatNightPlayer::RemoveInventory(int Index)
{
	if(Index==-1) return;
	Inventory[Index] = nullptr;
}


void ABeatNightPlayer::TraceEnemyToDamage(FVector StartLocation, FVector EndLocation, float WeaponDamage)
{
	FHitResult OutHitResult;
	GetWorld()->LineTraceSingleByChannel(OutHitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::White, false, 0.2f, 0, 0.1f);

	if(OutHitResult.bBlockingHit)
	{
		AEnemy* HitEnemy = Cast<AEnemy>(OutHitResult.Actor.Get());
		if(HitEnemy)
		{
			if(HitEnemy->GetDying()) return;
			const float RandomDamaged = RandomizationDamage(WeaponDamage);
			UGameplayStatics::ApplyDamage(HitEnemy, RandomDamaged, GetController(), this, UDamageType::StaticClass());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEnemy->GetDamagedParticle(), OutHitResult.Location, FRotator::ZeroRotator, FVector(2.f));
			// 데미지 UI 보여주기
			ShowHitNumber(RandomDamaged, OutHitResult.Location, HitEnemy->GetActorRotation());
		}
		else
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GunParticle, OutHitResult.Location);
		}
	}
}

float ABeatNightPlayer::RandomizationDamage(float Damage)
{
	int Rand = FMath::RandRange(Damage-10.f, Damage+10.f);
	if(Rand <= 0) return 0;
	return Rand;
}

void ABeatNightPlayer::BuyItem(AItem* Item, FName ItemName, uint8 ItemCoin, float Amount, USoundCue* SoundCue)
{
	bool IsBuy = false;
	if(ItemName.IsEqual("Defense"))
	{
		const uint8 PlayerCoin = GetItemCoins();
		if(PlayerCoin >= ItemCoin)
		{
			SetItemCoins(PlayerCoin - ItemCoin);
			SetDefense(GetDefense() + Amount);
			IsBuy = true;
		}
	}
	else if(ItemName.IsEqual("HP"))
	{

	}
	else if(ItemName.IsEqual("Upgrade"))
	{

	}
	else if(ItemName.IsEqual("Key"))
	{

	}
	if(IsBuy)
	{
		if(SoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
		}
		Item->Destroy();
		return;
	}
	// Coin 부족시 아이템 구매 실패 UI
	GetFailItemToShop();
}