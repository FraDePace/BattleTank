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

	auto PlayerTank = Cast<ATank>(GetPlayerTank());
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController founds player %s"), *(PlayerTank->GetName()));
	}


	UE_LOG(LogTemp, Warning, TEXT("AIPlayerController BeginPlay"));
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	return Cast<ATank>(PlayerTank);
}

