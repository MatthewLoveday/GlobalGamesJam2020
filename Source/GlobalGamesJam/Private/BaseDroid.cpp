// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDroid.h"

#include "GameFramework/Actor.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABaseDroid::ABaseDroid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TArray<USceneComponent*> components;
	this->GetComponents(components, true);

	USkeletalMeshComponent* skelly = nullptr;

	for (int32 i = 0; i < components.Num(); i++)
	{
		skelly = Cast<USkeletalMeshComponent>(components[i]);
		
		if (skelly != nullptr) 
		{
			skelly->DestroyComponent();
		}
	}


	//Add new static mesh component
	DroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Droid Mesh"));
}

// Called when the game starts or when spawned
void ABaseDroid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseDroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseDroid::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

