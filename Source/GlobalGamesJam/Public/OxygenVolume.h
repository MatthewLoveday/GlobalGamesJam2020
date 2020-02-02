// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "OxygenVolume.generated.h"

UCLASS()
class GLOBALGAMESJAM_API AOxygenVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOxygenVolume();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OxygenCount;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* boundingVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasLeak;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ATileBase*> RelevantTiles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AOxygenVolume*> NeighbouringOxygenVolumes;

	UFUNCTION(BlueprintCallable)
	void BalanceOxygenWithNeighbours();

	UFUNCTION(BlueprintCallable)
	void CheckForLeak();
	
	UPROPERTY(VisibleAnywhere)
	FTimerHandle CheckLeakHandle;

	UFUNCTION(BlueprintCallable)
	void HandleLeak(bool leak, float DeltaTime);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	float GetOxygenCount();

	UFUNCTION(BlueprintCallable)
	bool HasOxygen();

	UFUNCTION(BlueprintCallable)
	void ConsumeOxygen(float amount = 0.1f);
};
