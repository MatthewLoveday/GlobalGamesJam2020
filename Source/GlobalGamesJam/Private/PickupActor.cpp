// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupActor.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsBeingCarried = false;

	SM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM"));
	SM->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SM->SetCollisionProfileName(TEXT("Pickup"));
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	//Get Floor Location
	baseElevation = GetActorLocation().Z;
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::DropObject()
{
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, baseElevation));
	IsBeingCarried = false;
}

ERepairType APickupActor::MapItemTypeToRepairFunction(EItemType type)
{
	switch (type)
	{
	case EItemType::Battery:
		return ERepairType::AddBattery;
		break;

	case EItemType::InvalidItem:
	default:
		return ERepairType::None;
		break;
	}

	return ERepairType::None;
}

void APickupActor::BeginHover_Implementation()
{
	SM->SetRenderCustomDepth(true);
}

void APickupActor::EndHover_Implementation()
{
	SM->SetRenderCustomDepth(false);
}
