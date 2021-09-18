#pragma once

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Gun UMETA(DisplayName = "Gun"),
	EWT_Rope UMETA(DisplayName = "Rope")
};

UENUM(BlueprintType)
enum class ESwordType : uint8
{
	EST_Level1 UMETA(DisplayName = "Level1"),
	EST_Level2 UMETA(DisplayName = "Level2"),
	EST_Level3 UMETA(DisplayName = "Level3"),
	EST_Level4 UMETA(DisplayName = "Level4")
};