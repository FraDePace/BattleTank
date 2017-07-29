// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)  //BlueprintCallable, makes it possible to call aC++ function from Blueprint
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)  //BlueprintCallable, makes it possible to call aC++ function from Blueprint
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable)
	void Fire();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	

	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 100000; //1000 m/s TODO find sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint; //Alternative https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/

	//Limit the fire rate						
	UPROPERTY(EditDefaultsOnly, Category = Firing)	//EditDefaultsOnly ---> Apparirà solo nel blueprint	//EditAnywhere ---> Questa proprietà apparaira nel blueprint ma anche su ogni istanza del Tank. Posso renderlo custom per ognuno di loro
	float ReloadTimeInSeconds = 3.0f;

	//Local Barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;

	

	double LastFireTime = 0;
};
