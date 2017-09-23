// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;
		
	}
	FoundAimingComponent(AimingComponent);

	
}
void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		//Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);


	}
}
void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("DTank Died"));
	StartSpectatingOnly(); //Modalità spettatore
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Aim Towards CrossAir
	AimTowardsCrossAir();
}

void ATankPlayerController::AimTowardsCrossAir()
{
	if (!GetPawn()) {  //Controllo aggiunto per questo bug della funzione Tick: https://issues.unrealengine.com/issue/UE-36929
		return;
	}
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
	{
		return;

	}

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation))  //It is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// Tell controlled tank to aim at this points
		AimingComponent->AimAt(HitLocation);
		
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
	}

	return false;
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
			ECollisionChannel::ECC_Camera)
		)
	{
		// Set hit location
		HitLocation = HitResult.Location;

		return true;
	}

	HitLocation = FVector(0.f);
	return false;
}
