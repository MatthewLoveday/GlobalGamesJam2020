// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DroidPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API ADroidPlayerController : public APlayerController
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
	void MoveCharacterHorizontal(float value);

	UFUNCTION(BlueprintCallable)
	void MoveCharacterVertical(float value);

public:
	virtual void SetupInputComponent() override;
};
