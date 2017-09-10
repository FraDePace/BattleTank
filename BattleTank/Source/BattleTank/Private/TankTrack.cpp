// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);  //Metodo per capire quando tocchiamo il terreno 
}
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("hit ground"));
	//Drive the tracks
	DriveTrack();
	//Aplly sideways force
	ApplySidewaysForce();

	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{
	//Calculate the slippage spped
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//Work out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //Ci dice quanta accelerazione abbiamo in questo frame. La direzione è opposta al right vector.
																				 //Calculate and apply sideways force
	auto TankRootSceneComponent = GetOwner()->GetRootComponent();  //SceneComponent, per prenderne la massa dobbiamo accedere al StaticComponent
	auto TankRootStaticComponent = Cast<UStaticMeshComponent>(TankRootSceneComponent);
	auto CorrectionForce = (TankRootStaticComponent->GetMass() * CorrectionAcceleration) / 2; //forza da applicare a ciascun Track, per questo divido per due
	TankRootStaticComponent->AddForce(CorrectionForce);
}


void UTankTrack::SetThrottle(float Throttle)
{
	
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,+1);
	
	
}

void UTankTrack::DriveTrack()
{
	//clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxdrivingForce;
	auto ForceLocation = GetComponentLocation();
	AddForceAtLocation(ForceApplied, ForceLocation);
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
