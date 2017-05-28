// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(ControlledTank->GetName()));
	}


	UE_LOG(LogTemp, Warning, TEXT("PlayerController BeginPlay"));
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim Towards CrossAir
	UE_LOG(LogTemp, Warning, TEXT("PlayerController ticking"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
	
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossAir()
{
	if (!GetControlledTank())
	{
		return;
	}

	// Get world location if linetrace through crossair
	// If it hits the landscape
		// Tell controlled tank to aim ai this points
}
