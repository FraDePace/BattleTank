// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Called when the game starts
void ATank::BeginPlay()
{
	Super::BeginPlay();

	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ BeginPlay"), *Name);

}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointer as added at construction
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//UE_LOG(LogTemp, Warning, TEXT("%f, Find aim solution"), Time);
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ Construct"), *Name);

}

/*void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}*/

void ATank::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded) { 
		//Spawn a projectile a the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(4000);

		LastFireTime = FPlatformTime::Seconds();
	}

	
}


// Called to bind functionality to input
/*void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}*/

void ATank::AimAt(FVector HitLocation)
{
	
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

