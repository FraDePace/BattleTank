// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ensure(PlayerTank)) 
	{
		//Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);  //TODO check radius is in cm, Questo metdo inizia il pathfinding: l'output del pathfinding andrà poi usato come input nel NavMesh (col metodo RequestDirectMove)

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Fire if Ready
		ControlledTank->Fire();

	}
}



