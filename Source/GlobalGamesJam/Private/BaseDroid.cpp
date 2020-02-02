// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseDroid.h"

#include "GameFramework/Actor.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/SkeletalMeshActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DroidPlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "TileBase.h"


// Sets default values
ABaseDroid::ABaseDroid()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	//TArray<USceneComponent*> components;
	//this->GetComponents(components, true);

	//USkeletalMeshComponent* skelly = nullptr;

	//for (int32 i = 0; i < components.Num(); i++)
	//{
	//	skelly = Cast<USkeletalMeshComponent>(components[i]);
	//	
	//	if (skelly != nullptr) 
	//	{
	//		skelly->DestroyComponent();
	//	}
	//}

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 1000.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Add new static mesh component
	DroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Droid Mesh"));
	DroidMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DroidMesh->SetRelativeScale3D(FVector(2.5, 2.5, 2.5));
	DroidMesh->SetRelativeRotation(FRotator(0, -90, 0));
	DroidMesh->SetRelativeLocation(FVector(0, 0, -20));

	HandPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Hand Position"));
	HandPosition->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HandPosition->SetRelativeLocation(FVector(40, 0, -10));

	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level


	//Add a new droid camera
	DroidCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Droid Camera"));
	DroidCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	DroidCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	interactCollisionBoxSize = FVector(50.0f, 50.0f, 100.0f);
	
	InSkillcheck = false;
}

// Called when the game starts or when spawned
void ABaseDroid::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseDroid::DisableMovement()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->DisableMovement();
}

void ABaseDroid::EnableMovement()
{
	GetCharacterMovement()->StopMovementImmediately();
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void ABaseDroid::InteractWithTile_Implementation(ATileBase* tile)
{
	if(tile->NeedRepair())
	{		
		//Start Skillcheck
		InSkillcheck = true;
		
		//Turn off movement
		DisableMovement();
	}
}

void ABaseDroid::OnInteractionComplete_Implementation(ERepairType repairType, ATileBase* Tile)
{
	//do nothing
	InSkillcheck = false;
	
	Tile->RepairLayer();
}

bool ABaseDroid::CanDroidDoRepair(ERepairType repairType)
{
	for (int i = 0; i < AchievableRepairs.Num(); ++i)
	{
		if(repairType == AchievableRepairs[i])
		{
			return true;
		}
	}

	return false;
}

void ABaseDroid::MoveHorizontal(float value)
{
	//Move Horizontally in the world direction
	FVector MoveDirection = FVector(0, value, 0);
	AddMovementInput(MoveDirection);
}

void ABaseDroid::MoveVertical(float value)
{
	//Move Horizontally in the world direction
	FVector MoveDirection = FVector(value, 0, 0);
	AddMovementInput(MoveDirection);
}

// Called every frame
void ABaseDroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if picked item isn't nullptr
	if(CarriedItem != nullptr)
	{
		//Set position to hands position
		CarriedItem->SetActorLocation(HandPosition->GetComponentLocation());
	}
}

// Called to bind functionality to input
void ABaseDroid::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


}

void ABaseDroid::Dash()
{
	
}

void ABaseDroid::OnSkillcheckDown_Implementation()
{
	
}

void ABaseDroid::OnSkillcheckUp_Implementation()
{
	
}

bool DoesRepairTypeAcceptItem(ERepairType type)
{
	return type == ERepairType::AddBattery;
}

void ABaseDroid::Interact_Implementation()
{
	if(InSkillcheck)
	{
		return;
	}

	//Collision Boundaries
	FVector boxSize = FVector(50.0f, 50.0f, 100.0f);
	FVector boxPos = GetActorLocation() + (GetActorForwardVector() * 100.0f);

	FCollisionShape interactableDetector = FCollisionShape::MakeBox(boxSize);

	TArray<FHitResult> outHits;

	bool hit = false;

	//Detect for carried items if we aren't already carrying an item
	if(CarriedItem == nullptr && HasPickupAbility)
	{
		hit = GetWorld()->SweepMultiByChannel(outHits,
			boxPos,
			boxPos + GetActorForwardVector(),
			FQuat::Identity,
			ECC_GameTraceChannel3,
			interactableDetector);

		if(hit)
		{
			APickupActor* pickup;

			for (int32 i = 0; i < outHits.Num(); i++)
			{
				pickup = Cast<APickupActor>(outHits[i].Actor);

				if (pickup != nullptr)
				{
					CarriedItem = pickup;
					pickup->IsBeingCarried = true;
					break;
				}
			}
			
			return;
		}
	}

	//otherwise detect for repairable object
	//Detect interactable objects

	hit = GetWorld()->SweepMultiByChannel(outHits,
		boxPos,
		boxPos + GetActorForwardVector(),
		FQuat::Identity,
		ECC_GameTraceChannel1,
		interactableDetector);

	if (hit)
	{
		//outhits must have at least one member
		//cast outhit to ITile
		ATileBase* tileInterface;

		for (int32 i = 0; i < outHits.Num(); i++)
		{
			tileInterface = Cast<ATileBase>(outHits[i].Actor);

			if (tileInterface != nullptr)
			{
				if(tileInterface->IsRepairInProgress())
				{
					continue;
				}
				
				//if the tile has a repair function which uses the item
				if(CarriedItem != nullptr)
				{
					if (DoesRepairTypeAcceptItem(tileInterface->GetCurrentRepairType()))
					{
						//does the item type match?
						if (tileInterface->GetCurrentRepairType() == CarriedItem->MapItemTypeToRepairFunction(CarriedItem->ItemType))
						{
							tileInterface->RepairLayer();
							CarriedItem->Destroy();
							CarriedItem = nullptr;
							return;
						}
					}
				}
				else if(!DoesRepairTypeAcceptItem(tileInterface->GetCurrentRepairType()))
				{
					//otherwise it's a skill check
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interacting with tile"));

					//if the repair is achievable by this droid
					if(CanDroidDoRepair(tileInterface->GetCurrentRepairType()))
					{
						InteractWithTile(tileInterface);
					}
				}
				else
				{
					
				}
				break;
			}
		}

	}
	else
	{
		//if carrying an item, drop it
		if (CarriedItem != nullptr)
		{
			CarriedItem->DropObject();
			CarriedItem = nullptr;
			return;
		}
	}

	//THIS CODE PATH IS NEVER HIT IF AN ITEM WAS USED TO REPAIR A TILE
}

void ABaseDroid::CancelInteraction_Implementation()
{
	//Re-enable movement
	EnableMovement();

	
	InSkillcheck = false;
}

void ABaseDroid::OnRepairComplete_Implementation()
{
	//re-enable movement
	EnableMovement();

	InSkillcheck = false;
}

