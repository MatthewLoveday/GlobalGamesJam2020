// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "Human.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API AHuman : public APickupActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InOxygenatedState;

	UFUNCTION(BlueprintCallable)
	void SetOxygenated(bool oxygenated);
};
