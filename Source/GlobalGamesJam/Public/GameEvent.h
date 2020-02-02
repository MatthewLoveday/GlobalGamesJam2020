// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameEvent.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EGameEvent : uint8
{
	None = 0,
	MeteorShower,
	TravelThroughNebularStorm,
	AlienAttack,
	TravelPastBlackHole,
	MAX
};

