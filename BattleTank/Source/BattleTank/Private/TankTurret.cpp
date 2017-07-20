// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float r)
{
	SetRelativeRotation(FRotator(0, r, 0));
}


