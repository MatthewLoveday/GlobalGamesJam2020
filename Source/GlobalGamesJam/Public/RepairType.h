#pragma once

#include "CoreMinimal.h"
#include "RepairType.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ERepairType : uint8
{
	FixWiring 		UMETA(DisplayName = "Fix Wiring"),
	RevealPanel 	UMETA(DisplayName = "Reveal Panel"),
	SealPanel		UMETA(DisplayName = "Seal Panel"),
	AddBattery		UMETA(DisplayName = "Add Battery"),
	AddFuse		UMETA(DisplayName = "Add Fuse"),
	SealBreach		UMETA(DisplayName = "Fix Breach"),
	Extinguish		UMETA(DisplayName = "Extinguish"),
	None UMETA(DisplayName = "None")
};

