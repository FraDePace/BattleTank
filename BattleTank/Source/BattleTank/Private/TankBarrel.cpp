// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	
	//Move the barrel the right amount this frame
	//Given a max elevation and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; //frame rate independent
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;  //RelativeRotation.Pitch rotazione Pitch dello Static mesh
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	//UE_LOG(LogTemp, Warning, TEXT("RawNewElevation: %f"), RawNewElevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
