// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responisble for driving the Tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
	
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw); //tra -1 e +1

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	

private:

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	//TODO Check best protection, metodo trovato nella classe NavMeshComponent, ne faccio l'override. Calle from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);
};
