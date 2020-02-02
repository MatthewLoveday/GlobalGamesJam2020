// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TileDroidIcon.generated.h"

class ABaseDroid;
/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API UTileDroidIcon : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeIcon(ABaseDroid* RequestedDroid);
};
