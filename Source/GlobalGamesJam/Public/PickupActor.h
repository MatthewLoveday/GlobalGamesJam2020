// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RepairType.h"
#include "PickupActor.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EItemType : uint8
{
	Battery 		UMETA(DisplayName = "Battery"),
	Fuse 		UMETA(DisplayName = "Fuse"),
	InvalidItem		UMETA(DisplayName = "ERROR INVALID ITEM")
};




UCLASS()
class GLOBALGAMESJAM_API APickupActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBeingCarried;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SM;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float baseElevation;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DropObject();

	UFUNCTION(BlueprintCallable)
	ERepairType MapItemTypeToRepairFunction(EItemType type);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void BeginHover();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EndHover();
};
