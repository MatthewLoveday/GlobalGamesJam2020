// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Add default functionality here for any ITile functions that are not pure virtual.
bool ITile::NeedRepair_Implementation()
{
	if (m_RepairQueue.IsEmpty())
		return false;
	
	return true;
}

ERepairType ITile::GetCurrentRepairType_Implementation()
{
	ERepairType returnValue;
	m_RepairQueue.Peek(returnValue);
	return returnValue;
}
ITile::Callback ITile::Repair_Implementation(DroidCallback onComplete)
{
	m_OnComplete = onComplete;

	return &ITile::OnCancel;
}
