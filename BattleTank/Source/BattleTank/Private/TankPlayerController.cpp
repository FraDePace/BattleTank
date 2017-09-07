// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
		
	}
	FoundAimingComponent(AimingComponent);

	
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim Towards CrossAir
	AimTowardsCrossAir();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossAir()
{
	if (!ensure(GetControlledTank()))
	{
		return;
	}

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))  //It is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// Tell controlled tank to aim at this points
		GetControlledTank()->AimAt(HitLocation);
	}
	
	
	
		
}
// Get world location if linetrace through crossair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//Find the crosshair position in pixell coordinate
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
		// Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;  //The world direction
	
	//Convert current mouse 2D position to World Space 3D position and direction. Returns false if unable to determine value.
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation,
		LookDirection);

	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();     //Partiamo dalla camera
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	//If line trace Succeeds
	if (GetWorld()->LineTraceSingleByChannel(   //Trace a ray against the world using a specific channel and return the first blocking hit
												//TRUE if a blocking hit is found
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
	{
		// Set hit location
		HitLocation = HitResult.Location;

		return true;
	}

	HitLocation = FVector(0.f);
	return false;
}
