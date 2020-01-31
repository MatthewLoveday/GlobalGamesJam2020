// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RepairType.h"
#include "GameFramework/Character.h"
#include "BaseDroid.generated.h"

UCLASS()
class GLOBALGAMESJAM_API ABaseDroid : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseDroid();

	//to be set in the blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ERepairType>	AchievableRepairs;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DroidMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
