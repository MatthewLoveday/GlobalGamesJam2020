// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RepairType.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "BaseDroid.generated.h"

class ATileBase;
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

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* DroidCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DisableMovement();

	UFUNCTION(BlueprintCallable)
	void EnableMovement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool InSkillcheck;
	
public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InteractWithTile(ATileBase* tile);

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteractionComplete(ERepairType repairType, ATileBase* Tile);
	
	//Movement Functions
	UFUNCTION()
	void MoveHorizontal(float value);

	UFUNCTION()
	void MoveVertical(float value);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector interactCollisionBoxSize;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CancelInteraction();

	UFUNCTION(BlueprintCallable)
	void Dash();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSkillcheckDown();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSkillcheckUp();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnRepairComplete();
};
