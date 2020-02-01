// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"

// Sets default values
ATileBase::ATileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileBase::Repair(DroidCallback onComplete, ABaseDroid* droid)
{
	if(m_RepairQueue.Num() != 0)
	{
		ERepairType type = m_RepairQueue[0];
		m_RepairQueue.RemoveAt(0);
		
		(droid->* (onComplete))(type);

		OnRepair(type);
	}
}

void ATileBase::OnHover_Implementation()
{
	
}

bool ATileBase::NeedRepair_Implementation()
{
	return (m_RepairQueue.Num() != 0);
}

ERepairType ATileBase::GetCurrentRepairType_Implementation()
{
	return m_RepairQueue[0];
}

