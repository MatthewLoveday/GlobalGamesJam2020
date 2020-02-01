// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGamesJamGameModeBase.h"

#include "DroidPlayerController.h"
#include "BaseDroid.h"

AGlobalGamesJamGameModeBase::AGlobalGamesJamGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADroidPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
		DefaultPawnClass = ABaseDroid::StaticClass();
	//}
}