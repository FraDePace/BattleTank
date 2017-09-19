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
	Locked,
	OutOfAmmo
};

//Forward Declaration
class UTankBarrel;  
class UTankTurret;
class AProjectile;

//Hold barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:	

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000; //1000 m/s TODO find sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/

	double LastFireTime = 0;
													  //Limit the fire rate						
	UPROPERTY(EditDefaultsOnly, Category = Firing)	//EditDefaultsOnly ---> Apparirà solo nel blueprint	//EditAnywhere ---> Questa proprietà apparaira nel blueprint ma anche su ogni istanza del Tank. Posso renderlo custom per ognuno di loro
	float ReloadTimeInSeconds = 3.0f;

	bool IsBarrelMoving();
	FVector AimDir;

	int RoundLeft = 3;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//void AimAt(FVector HitLocation, float LaunchSpeed);
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();

	EFiringStatus GetFiringStatus() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundLeft() const;
};
