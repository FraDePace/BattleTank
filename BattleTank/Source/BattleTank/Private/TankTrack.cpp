// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Calculate the slippage spped
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work out the required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //Ci dice quanta accelerazione abbiamo in questo frame. La direzione � opposta al right vector.
	//Calculate and apply sideways force
	auto TankRootSceneComponent = GetOwner()->GetRootComponent();  //SceneComponent, per prenderne la massa dobbiamo accedere al StaticComponent
	auto TankRootStaticComponent = Cast<UStaticMeshComponent>(TankRootSceneComponent);
	auto CorrectionForce = (TankRootStaticComponent->GetMass() * CorrectionAcceleration) / 2; //forza da applicare a ciascun Track, per questo divido per due
	TankRootStaticComponent->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	

	//clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxdrivingForce;
	auto ForceLocation = GetComponentLocation();
	AddForceAtLocation(ForceApplied, ForceLocation);
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	
}