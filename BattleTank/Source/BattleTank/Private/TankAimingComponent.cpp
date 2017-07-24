// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace); //The last parameter must be to avoid bugs



	if (bHaveAimSolution) //Calculate the OutLaunchVelocity
	{
		
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();  //GetSafeNormal(), this method provides a vector of the same direction but unit length. 
																//If the vector you provide is too short you'll get (0,0,0) back.
		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(AimDirection);
		//auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f, Find aim solution"), Time);
	}
	else  //No solution
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f, No aim solution"), Time);
	}


	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Work-out didderence between current barrel rotation and AimDirection
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();  //Esempio: FVector(1.0, 1.0, 0) ----> FRotator = Pitch = 0, Roll = 0, Yaw = 0.
																  //A vector that points equally down the X and Y axis is "Yawed" by 45 degrees clockwise as seen from above.
																  //Note Roll may be null as we have said nothing about Roll so it can't be inferred (we're pointing the arrow not rotating it when we create the FVector)
	//UE_LOG(LogTemp, Warning, TEXT("%s BarrelRotation.Rotation: %s"), *GetOwner()->GetName(), *BarrelRotation.ToString());
	auto AimAsRotator = AimDirection.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s AimAsRotator.Rotation: %s"), *GetOwner()->GetName(),*AimAsRotator.ToString());
	auto DeltaRotator = AimAsRotator - BarrelRotation;
	//UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator: %s"), *GetOwner()->GetName(), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::RotateTurretTowards(FVector Rotation)
{


	//UE_LOG(LogTemp, Warning, TEXT("Turret: %s"), *Turret->GetName());
	auto TurretRotation = Turret->GetForwardVector().Rotation();
	
	auto RotationasRotator = Rotation.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s AimAsRotator.Rotation: %s"), *GetOwner()->GetName(),*AimAsRotator.ToString());
	auto DeltaRotator = RotationasRotator - TurretRotation;
	//UE_LOG(LogTemp, Warning, TEXT("%s DeltaRotator: %s"), *GetOwner()->GetName(), *DeltaRotator.ToString());
	Turret->Rotate(DeltaRotator.Yaw);
}

