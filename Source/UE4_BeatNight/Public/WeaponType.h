#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Gun UMETA(DisplayName = "Gun"),
	EWT_Rope UMETA(DisplayName = "Rope")
};

UENUM(BlueprintType)
enum class EWeaponName : uint8
{
	EWN_Noraml UMETA(DisplayName = "Normal"),
	EWN_Anaconda UMETA(DisplayName = "Anaconda"),
	EWN_ColtDouble UMETA(DisplayName = "ColtDouble"),
	EWN_Remington UMETA(DisplayName = "Remington"),
	EWN_ShotGun UMETA(DisplayName = "ShotGun"),
	EWN_Winchester UMETA(DisplayName = "Winchester")
};

UENUM(BlueprintType)
enum class ESwordType : uint8
{
	EST_Level1 UMETA(DisplayName = "Level1"),
	EST_Level2 UMETA(DisplayName = "Level2"),
	EST_Level3 UMETA(DisplayName = "Level3"),
	EST_Level4 UMETA(DisplayName = "Level4")
};
