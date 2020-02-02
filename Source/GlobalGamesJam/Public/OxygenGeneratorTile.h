// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileBase.h"
#include "OxygenGeneratorTile.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API AOxygenGeneratorTile : public ATileBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GenerationRate;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	AOxygenGeneratorTile();
};
