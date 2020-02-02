// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"
#include "GlobalGamesJamGameModeBase.h"
// Sets default values
ATileBase::ATileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	staticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	if(m_RepairQueue.Num() > 0)
	{
		UpdateMeshAccordingToCurrentRepairType();
		
	}
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();



	AGlobalGamesJamGameModeBase* gameMode = Cast<AGlobalGamesJamGameModeBase>(GetWorld()->GetAuthGameMode());
	gameMode->RegisterTile(this);

	if (m_RepairQueue.Num() > 0)
	{
		UpdateMeshAccordingToCurrentRepairType();
		gameMode->RegisterBuildTask(this);
	}
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRepairData ATileBase::SearchArrayForRepairType(ERepairType type)
{
	for(int32 i = 0; i < m_MeshToRepairType.Num(); i++)
	{
		if(m_MeshToRepairType[i].repairType == type)
		{
			return m_MeshToRepairType[i];
		}
	}

	//return empty
	return FRepairData();
}

void ATileBase::OnRepair_Implementation(ERepairType old)
{
	if(NeedRepair())
	{
		isInRepair = false;
	}
}

void ATileBase::RepairLayer()
{
	if(m_RepairQueue.Num() != 0)
	{
		OnRepair(m_RepairQueue[0]);
		m_RepairQueue.RemoveAt(0);

		UpdateMeshAccordingToCurrentRepairType();
	}


	if(m_RepairQueue.Num() == 0)
	{
		//Increment Global Broken Count
		AGlobalGamesJamGameModeBase* gameMode = Cast<AGlobalGamesJamGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->BrokenTileCount--;
	}
	
	isInRepair = false;

}

bool ATileBase::IsRepaired()
{
	return !NeedRepair();
}

void ATileBase::OnRepairFail()
{
	isInRepair = false;
}

void ATileBase::UpdateMeshAccordingToCurrentRepairType()
{
	if(m_RepairQueue.Num() > 0)
	{
		FRepairData data = SearchArrayForRepairType(m_RepairQueue[0]);

		if(data.mesh != nullptr)
		{
			staticMesh->SetStaticMesh(data.mesh);
		}
	}
	else
	{
		if(DefaultRepairedMesh != nullptr)
		{
			staticMesh->SetStaticMesh(DefaultRepairedMesh);
		}
	}
}

void ATileBase::QueueRepairs(TArray<ERepairType> repairs)
{
	m_RepairQueue = repairs;
}

TArray<ERepairType> ATileBase::GetRepairQueue()
{
	return m_RepairQueue;
}

bool ATileBase::HasRepairWhichLeaksOxygen()
{
	for(int i = 0; i < m_RepairQueue.Num(); i++)
	{
		//todo add more repair types
		if(m_RepairQueue[i] == ERepairType::SealBreach)
		{
			return true;
		}
	}

	return false;
}

void ATileBase::BeginHover()
{
	staticMesh->SetRenderCustomDepth(true);
}

void ATileBase::EndHover()
{
	staticMesh->SetRenderCustomDepth(false);
}

void ATileBase::AddDefaultRepairsAndRegenMesh()
{
	AddDefaultRepairsToQueue();
	UpdateMeshAccordingToCurrentRepairType();

	//Increment Global Broken Count

}

void ATileBase::AddDefaultRepairsToQueue()
{
	//if it wasn't already broken then add it to global broken count
	if(m_RepairQueue.Num() == 0)
	{
		AGlobalGamesJamGameModeBase* gameMode = Cast<AGlobalGamesJamGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->BrokenTileCount++;
	}
	
	//empty the repair queue
	m_RepairQueue.Empty();
	
	//Fill it with new ones
	m_RepairQueue = defaultRepairQueue;
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
	if(m_RepairQueue.Num() > 0)
	{
		return m_RepairQueue[0];
	}
	else
	{
		return ERepairType::None;
	}
}

