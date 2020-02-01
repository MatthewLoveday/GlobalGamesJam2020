// Fill out your copyright notice in the Description page of Project Settings.


#include "DroidPlayerController.h"

#include "BaseDroid.h"

void ADroidPlayerController::MoveCharacterHorizontal(float value)
{
	//cast pawn
	if(GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->MoveHorizontal(value);
	}
}

void ADroidPlayerController::MoveCharacterVertical(float value)
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->MoveVertical(value);
	}
}

void ADroidPlayerController::Interact()
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->Interact();
	}
}

void ADroidPlayerController::CancelInteract()
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->CancelInteraction();
	}
}

void ADroidPlayerController::Dash()
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->Dash();
	}
}

void ADroidPlayerController::SkillcheckDown()
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->OnSkillcheckDown();
	}
}

void ADroidPlayerController::SkillcheckUp()
{
	if (GetPawn())
	{
		Cast<ABaseDroid>(GetPawn())->OnSkillcheckUp();
	}
}

void ADroidPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	//Forward Input To Possessed Droid
	InputComponent->BindAxis("HorizontalMove", this, &ADroidPlayerController::MoveCharacterHorizontal);
	InputComponent->BindAxis("VerticalMove", this, &ADroidPlayerController::MoveCharacterVertical);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADroidPlayerController::Interact);
	InputComponent->BindAction("Cancel", IE_Pressed, this, &ADroidPlayerController::CancelInteract);

	
	InputComponent->BindAction("SkillCheck", IE_Pressed, this, &ADroidPlayerController::SkillcheckDown);
	InputComponent->BindAction("SkillCheck", IE_Released, this, &ADroidPlayerController::SkillcheckUp);
}
