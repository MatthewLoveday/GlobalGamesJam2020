// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Add default functionality here for any UTile functions that are not pure virtual.
bool ATile::NeedRepair_Implementation()
{
	if (m_RepairQueue.IsEmpty())
		return false;
	
	return true;
}

ERepairType ATile::GetCurrentRepairType_Implementation()
{
	ERepairType returnValue;
	m_RepairQueue.Peek(returnValue);
	return returnValue;
}

void ATile::Repair(DroidCallback onComplete, ABaseDroid* droid)
{
	if(!m_RepairQueue.IsEmpty())
	{
		ERepairType type;
		m_RepairQueue.Peek(type);
		m_RepairQueue.Pop();
		
		(droid->* (onComplete))(type);

		OnRepair(type);
	}
}

void ATile::OnHover_Implementation()
{
	//Do Nothing
}