// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximun driving force and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))  //to make a component blueprint spawnable
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//Sets a Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

	//Max Force per Track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxdrivingForce = 400000; //Assume 40 tonne tank and 1g acceleration
};