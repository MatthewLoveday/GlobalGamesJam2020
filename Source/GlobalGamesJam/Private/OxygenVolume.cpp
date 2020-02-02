// Fill out your copyright notice in the Description page of Project Settings.


#include "OxygenVolume.h"
#include "TimerManager.h"
#include "TileBase.h"
#include "Human.h"
#include "OxygenGeneratorTile.h"

// Sets default values
AOxygenVolume::AOxygenVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boundingVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Oxygen Volume"));
	boundingVolume->SetBoxExtent(FVector(500, 500, 500));
	boundingVolume->SetCollisionProfileName("OxygenVolume");
	SetRootComponent(boundingVolume);

	OxygenCount = 100;
	HasLeak = false;
	LeakCount = 0;
}

// Called when the game starts or when spawned
void AOxygenVolume::BeginPlay()
{
	Super::BeginPlay();

	//Gather Relevant Tiles
	TArray<AActor*> actors;
	GetOverlappingActors(actors, ATileBase::StaticClass());

	for (int i = 0; i < actors.Num(); ++i)
	{
		RelevantTiles.Add(Cast<ATileBase>(actors[i]));
	}


	//Gether Relevant Oxygen Volumes

	GetOverlappingActors(actors, StaticClass());

	for (int i = 0; i < actors.Num(); ++i)
	{
		NeighbouringOxygenVolumes.Add(Cast<AOxygenVolume>(actors[i]));
	}

	//Gather Oxygen Generators
	GetOverlappingActors(actors, AOxygenGeneratorTile::StaticClass());
	
	for (int i = 0; i < actors.Num(); ++i)
	{
		OxygenGeneratorTiles.Add(Cast<AOxygenGeneratorTile>(actors[i]));
	}
	
	
	GetWorld()->GetTimerManager().SetTimer(CheckLeakHandle, this, &AOxygenVolume::CheckForLeak, 3.0f, true);
	GetWorld()->GetTimerManager().SetTimer(SetOxygenatedStateForHumansHandle, this, &AOxygenVolume::SetOxygenatedStateForHumans, 3.0f, true);
}

void AOxygenVolume::BalanceOxygenWithNeighbours(float DeltaTime)
{
	//if any neighbour has less oxygen, send it 0.01;
	for(int i = 0; i < NeighbouringOxygenVolumes.Num(); i++)
	{
		if(OxygenCount > NeighbouringOxygenVolumes[i]->GetOxygenCount())
		{
			float o2Delta = FMath::Max(FMath::Abs(NeighbouringOxygenVolumes[i]->OxygenCount - OxygenCount), 0.8f);
			
			NeighbouringOxygenVolumes[i]->OxygenCount += 1.0f * o2Delta * DeltaTime;
			OxygenCount -= 1.0f * o2Delta * DeltaTime;
		}
	}
}

void AOxygenVolume::CheckForLeak()
{
	HasLeak = false;
	LeakCount = 0;
	
	for (int i = 0; i < RelevantTiles.Num(); i++)
	{
		if(RelevantTiles[i]->HasRepairWhichLeaksOxygen())
		{
			HasLeak = true;
			LeakCount++;
		}
	}

}

float AOxygenVolume::GetOxygenCount()
{
	return OxygenCount;
}

bool AOxygenVolume::HasOxygen()
{
	return OxygenCount > 0.1f;
}

void AOxygenVolume::ConsumeOxygen(float amount)
{
	OxygenCount -= amount;
}

void AOxygenVolume::HandleLeak(bool leak, float DeltaTime)
{
	if(!leak)
	{
		return;
	}

	OxygenCount -= 1.0f * (LeakCount * 2.0f) * DeltaTime;
}

void AOxygenVolume::TickOxygenGenerator(float DeltaTime)
{
	for(int i = 0; i < OxygenGeneratorTiles.Num(); i++)
	{
		//if it's fully working
		if(!OxygenGeneratorTiles[i]->NeedRepair())
		{
			OxygenCount += OxygenGeneratorTiles[i]->GenerationRate * DeltaTime;
		}
	}
}

// Called every frame
void AOxygenVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BalanceOxygenWithNeighbours(DeltaTime);

	HandleLeak(HasLeak, DeltaTime);

	TickOxygenGenerator(DeltaTime);

	if(OxygenCount > 100.0f)
	{
		OxygenCount = 100.0f;
	}
}

void AOxygenVolume::SetOxygenatedStateForHumans()
{
	TArray<AActor*> Humans;
	GetOverlappingActors(Humans, AHuman::StaticClass());

	for (int i = 0; i < Humans.Num(); ++i)
	{
		Cast<AHuman>(Humans[i])->InOxygenatedState = HasOxygen();

		ConsumeOxygen(2.0f);
	}
}

