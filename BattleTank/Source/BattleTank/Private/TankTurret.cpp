// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator: %s"), *GetOwner()->GetName(), r);
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; //frame rate independent
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;  //RelativeRotation.Pitch rotazione Pitch dello Static mesh
	
	//UE_LOG(LogTemp, Warning, TEXT("RawNewElevation: %f"), RawNewElevation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}


