// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement"));
	ProjectileMovement->bAutoActivate = false; //qualcosa con il fly off, bo--- Non "fly off" quando è costruito, lo setteremo quando spariamo?

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); //Questo vettore dovrebbe essere lo stesso del Barrel (vedi "Tank.Fire() ---> in GetSocket prendo la roatazione del Barrel)
	ProjectileMovement->Activate();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

