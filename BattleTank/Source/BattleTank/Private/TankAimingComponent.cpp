// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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
	//Super::BeginPlay();

	LastFireTime = FPlatformTime::Seconds();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
	if (isReloaded)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !Barrel->GetForwardVector().Equals(AimDir, 0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { 
		
		return; 
	}
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
		
		AimDir = OutLaunchVelocity.GetSafeNormal();  //GetSafeNormal(), this method provides a vector of the same direction but unit length. 
																//If the vector you provide is too short you'll get (0,0,0) back.
		MoveBarrelTowards(AimDir);
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{

	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}
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

	Turret->Rotate(DeltaRotator.Yaw);

}


void UTankAimingComponent::Fire()
{
	
	
	if (FiringState != EFiringStatus::Reloading) {
		//Spawn a projectile a the socket location of the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(4000);

		LastFireTime = FPlatformTime::Seconds();
	}


}


