// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum firing status to change color of th dot
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel;  
class UTankTurret;

//Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void RotateTurretTowards(FVector Rotation);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000; //1000 m/s TODO find sensible default

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Locked;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//void AimAt(FVector HitLocation, float LaunchSpeed);
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	
};
