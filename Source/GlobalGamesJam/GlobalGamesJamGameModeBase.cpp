// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGamesJamGameModeBase.h"

#include "DroidPlayerController.h"
#include "BaseDroid.h"
#include "TileBase.h"
#include "Math/UnrealMathUtility.h"

ATileBase* AGlobalGamesJamGameModeBase::GetRandomTile()
{
	if(GlobalTileList.Num() == 0)
	{
		return nullptr;
	}

	return GlobalTileList[FMath::RandRange(0, GlobalTileList.Num() - 1)];

	BrokenTileCount = 0;
}

void AGlobalGamesJamGameModeBase::RegisterBuildTask(ATileBase* newBuildTask)
{
	if(newBuildTask->NeedRepair())
	{
		RepairQueue.Emplace(newBuildTask);
	}
	
	BrokenTileCount = 0;
}

void AGlobalGamesJamGameModeBase::RegisterTile(ATileBase* newTile)
{
	GlobalTileList.Add(newTile);
}

void AGlobalGamesJamGameModeBase::HandleEvent(EGameEvent gameEvent)
{
	//dispatch event to relevant functions
	currentGameEvent = gameEvent;
}

EGameEvent AGlobalGamesJamGameModeBase::GetRandomGameEvent()
{
	return (EGameEvent)FMath::RandRange(0, (uint8)EGameEvent::MAX - 1);
}

AGlobalGamesJamGameModeBase::AGlobalGamesJamGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADroidPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	DefaultPawnClass = ABaseDroid::StaticClass();

	RepairQueue = TArray<ATileBase*>();
}
