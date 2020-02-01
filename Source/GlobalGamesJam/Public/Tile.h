// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RepairType.h"
#include "Containers/Queue.h"
#include "BaseDroid.h"
#include "Tile.generated.h"

UENUM(BlueprintType)
enum class ESkillCheckType : uint8
{
	HoldButtonDown UMETA(DisplayName = "Hold Button Down"),
	MashButton UMETA(DisplayName = "Mash Button"),
	TimedPress UMETA(DisplayName = "Timed Key Press"),
	RandomCheck UMETA(DisplayName = "Random Skill Check")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UTile : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class GLOBALGAMESJAM_API ITile
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Add queue of repairs which will be added when current thing is repaired

	TQueue<ERepairType> m_RepairQueue;

	typedef void(ITile::*Callback)(void);
	typedef void(ABaseDroid::*DroidCallback)(ERepairType);

	DroidCallback m_OnComplete;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool NeedRepair();
	virtual bool NeedRepair_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ERepairType GetCurrentRepairType();
	virtual ERepairType GetCurrentRepairType_Implementation();
	
	virtual void Repair(DroidCallback onComplete, ABaseDroid* droid);

		//void OnComplete(Callback onCompletePtr);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnHover();
	virtual void OnHover_Implementation();


};
