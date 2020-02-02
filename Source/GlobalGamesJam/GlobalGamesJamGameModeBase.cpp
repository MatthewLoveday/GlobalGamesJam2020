// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGamesJamGameModeBase.h"

#include "DroidPlayerController.h"
#include "BaseDroid.h"
#include "TileBase.h"

void AGlobalGamesJamGameModeBase::RegisterBuildTask(ATileBase* newBuildTask)
{
	if(newBuildTask->NeedRepair())
	{
		RepairQueue.Emplace(newBuildTask);
	}
}

AGlobalGamesJamGameModeBase::AGlobalGamesJamGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADroidPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	DefaultPawnClass = ABaseDroid::StaticClass();

	RepairQueue = TArray<ATileBase*>();
}
