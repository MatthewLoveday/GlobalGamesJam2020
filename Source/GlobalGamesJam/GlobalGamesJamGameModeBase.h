// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameEvent.h"
#include "TileDroidIcon.h"
#include "OxygenVolume.h"
#include "GlobalGamesJamGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GLOBALGAMESJAM_API AGlobalGamesJamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGameEvent currentGameEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AOxygenVolume* o2Volume;
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class ATileBase*> RepairQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ATileBase*> GlobalTileList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BrokenTileCount;
	
	UFUNCTION(BlueprintCallable)
	ATileBase* GetRandomTile();
	
	UFUNCTION(BlueprintCallable)
	void RegisterBuildTask(ATileBase* newBuildTask);

	UFUNCTION(BlueprintCallable)
	void RegisterTile(ATileBase* newTile);
	
	UFUNCTION(BlueprintCallable)
	void HandleEvent(EGameEvent gameEvent);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DoGameEvent(EGameEvent current);

	UFUNCTION(BlueprintCallable)
	EGameEvent GetRandomGameEvent();

	UFUNCTION(BlueprintCallable)
	int GetOxygenLevelPercent();
	
	AGlobalGamesJamGameModeBase();
};
