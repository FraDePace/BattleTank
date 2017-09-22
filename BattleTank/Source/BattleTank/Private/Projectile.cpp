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

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	//Quando colpisco qualcosa, setto come Rootl'ImpactBlast e distruggo il CollisionMesh per evitare che rimangano i proiettili 
	//Il Prjectile_BP rimane
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	//Damage Enemy Tank
	UGameplayStatics::ApplyRadialDamage(    //Applica un danno radiale, ok con esplosione proiettile.
		this,
		ProjectileDamage,
		GetActorLocation(),                //Da dove iniziare il danno
		ExplosionForce->Radius,         
		UDamageType::StaticClass(),
		TArray<AActor*>()   //damage all actors. In automatico verrà chiamato un metodo (se dichiarato) su tutte le calssi che ereditano d AActor, TakeDamage()
		);

	//Implemento un Timer, quando scade, il Projectile_BP viene distrutto
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::TimeEnd, DestroyDelay, false);
}

//Chiamato quando finisce il SeTimer()
void AProjectile::TimeEnd()
{
	Destroy();
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


