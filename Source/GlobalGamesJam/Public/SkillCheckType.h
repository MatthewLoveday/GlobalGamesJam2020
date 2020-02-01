#pragma once

#include "CoreMinimal.h"

#include "SkillCheckType.generated.h"

UENUM(BlueprintType)
enum class ESkillCheckType : uint8
{
	HoldButtonDown UMETA(DisplayName = "Hold Button Down"),
	MashButton UMETA(DisplayName = "Mash Button"),
	TimedPress UMETA(DisplayName = "Timed Key Press"),
	RandomCheck UMETA(DisplayName = "Random Skill Check")
};