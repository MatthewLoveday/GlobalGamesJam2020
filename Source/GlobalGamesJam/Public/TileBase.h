// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RepairType.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Map.h"
#include "BaseDroid.h"
#include "TileBase.generated.h"

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
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ERepairType, UStaticMesh*> m_MeshToRepairType;



	//Interface Calls
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ERepairType GetCurrentRepairType();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool NeedRepair();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnHover();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnRepair(ERepairType old);

	typedef void(ABaseDroid::* DroidCallback)(ERepairType);
	
	void Repair(DroidCallback onComplete, ABaseDroid* droid);
};
