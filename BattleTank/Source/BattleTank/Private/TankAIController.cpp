// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{

	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = Cast<ATank>(GetPawn());
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController possesing %s"), *(ControlledTank->GetName()));
	}


	UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay"));
}

