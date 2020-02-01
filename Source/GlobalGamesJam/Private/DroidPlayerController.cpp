// Fill out your copyright notice in the Description page of Project Settings.


#include "DroidPlayerController.h"

#include "BaseDroid.h"

void ADroidPlayerController::MoveCharacterHorizontal(float value)
{
	//cast pawn
	Cast<ABaseDroid>(GetPawn())->MoveHorizontal(value);
}

void ADroidPlayerController::MoveCharacterVertical(float value)
{
	Cast<ABaseDroid>(GetPawn())->MoveVertical (value);
}

void ADroidPlayerController::Interact()
{
	Cast<ABaseDroid>(GetPawn())->Interact();
}

void ADroidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	//Forward Input To Possessed Droid
	InputComponent->BindAxis("HorizontalMove", this, &ADroidPlayerController::MoveCharacterHorizontal);
	InputComponent->BindAxis("VerticalMove", this, &ADroidPlayerController::MoveCharacterVertical);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADroidPlayerController::Interact);
}
