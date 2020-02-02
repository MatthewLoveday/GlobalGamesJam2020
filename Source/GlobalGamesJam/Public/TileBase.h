// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RepairType.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "BaseDroid.h"
#include "SkillCheckType.h"
#include "TileBase.generated.h"

USTRUCT(BlueprintType)
struct FRepairData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ERepairType repairType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillCheckType skillcheckType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* mesh;
};

UCLASS()
class GLOBALGAMESJAM_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ERepairType> m_RepairQueue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool isInRepair;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* DefaultRepairedMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRepairData> m_MeshToRepairType;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FRepairData SearchArrayForRepairType(ERepairType type);

	//Interface Calls
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ERepairType GetCurrentRepairType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
	bool NeedRepair();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHover();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnRepair(ERepairType old);

	typedef void(ABaseDroid::* DroidCallback)(ERepairType);

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsRepairInProgress() const { return isInRepair; }

	UFUNCTION(BlueprintCallable)
	void RepairLayer();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsRepaired();

	UFUNCTION(BlueprintCallable)
		void OnRepairFail();

	UFUNCTION(BlueprintCallable)
	void UpdateMeshAccordingToCurrentRepairType();

	UFUNCTION(BlueprintCallable)
	void QueueRepairs(TArray<ERepairType> repairs);

	UFUNCTION(BlueprintCallable)
	TArray<ERepairType> GetRepairQueue();
};
