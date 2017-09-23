// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:


	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;  //Get called when the Pawn is possessed. 
												   //When TankAIController gets possessed, this method gets called.

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPossessedTankDeath();
	
protected:


	//How close can the AI tank
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 300;
};
