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

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void CancelInteract();

	UFUNCTION(BlueprintCallable)
	void Dash();
	
	UFUNCTION(BlueprintCallable)
	void SkillcheckDown();

	UFUNCTION(BlueprintCallable)
	void SkillcheckUp();
	
public:
	virtual void SetupInputComponent() override;
};
