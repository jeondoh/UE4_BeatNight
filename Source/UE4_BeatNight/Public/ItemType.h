#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_Normal UMETA(DisplayName = "Normal"),
	EIT_Store UMETA(DisplayName = "Store")
};