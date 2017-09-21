// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);  //La checkbox (sul blueprint) "Simulation Generate Hit Event" sara checcata di default
	CollisionMesh->SetVisibility(false); 

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); //Parentela con il Root (Collision Mesh)

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform); //Parentela con il Root (Collision Mesh)
	ImpactBlast->bAutoActivate = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile movement"));
	ProjectileMovement->bAutoActivate = false; //qualcosa con il fly off, bo--- Non "fly off" quando è costruito, lo setteremo quando spariamo?

	
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	//UE_LOG(LogTemp, Warning, TEXT("Fire!"));
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); //Questo vettore dovrebbe essere lo stesso del Barrel (vedi "Tank.Fire() ---> in GetSocket prendo la roatazione del Barrel)
	ProjectileMovement->Activate();
}


