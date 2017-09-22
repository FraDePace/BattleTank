// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);  //cast float to int32
	int32 DamageToApply = FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("DamageToApply: %d"), DamageToApply);
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("DTank Died"));
	}

	return DamageToApply;
}



