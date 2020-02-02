// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "GlobalGamesJamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API AGlobalGamesJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ATileBase*> RepairQueue;

	UFUNCTION(BlueprintCallable)
	void RegisterBuildTask(ATileBase* newBuildTask);
	
	AGlobalGamesJamGameModeBase();
};
