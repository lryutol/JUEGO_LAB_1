#include "AventuraUSFX022026L1Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Enemigo.h"
#include "AventuraUSFX022026L1Pawn.h"
#include "Torreta.h"
#include "UObject/ConstructorHelpers.h"

AAventuraUSFX022026L1Projectile::AAventuraUSFX022026L1Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);

	RootComponent = CollisionComponent;
	CollisionComponent->OnComponentHit.AddDynamic(this, &AAventuraUSFX022026L1Projectile::OnHit);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (ProjectileMesh.Succeeded()) MeshComponent->SetStaticMesh(ProjectileMesh.Object);
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 3.0f;
}

void AAventuraUSFX022026L1Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void AAventuraUSFX022026L1Projectile::SetVelocidad(float NuevaVelocidad)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = NuevaVelocidad;
		ProjectileMovement->MaxSpeed = NuevaVelocidad;
	}
}

void AAventuraUSFX022026L1Projectile::IgnorarActor(AActor* ActorParaIgnorar)
{
	if (CollisionComponent && ActorParaIgnorar)
	{
		// CORRECCIÓN: Solo se llama en el componente de colisión
		CollisionComponent->IgnoreActorWhenMoving(ActorParaIgnorar, true);
	}
}

void AAventuraUSFX022026L1Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA(AAventuraUSFX022026L1Projectile::StaticClass()))
	{
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		if (GetOwner() && GetOwner()->IsA(AEnemigo::StaticClass()))
		{
			if (OtherActor->IsA(AAventuraUSFX022026L1Pawn::StaticClass()))
			{
				UGameplayStatics::ApplyDamage(OtherActor, DanioProyectil, GetInstigatorController(), this, UDamageType::StaticClass());
				Destroy();
			}
		}
		else if (GetOwner() && GetOwner()->IsA(AAventuraUSFX022026L1Pawn::StaticClass()))
		{
			if (OtherActor->IsA(AEnemigo::StaticClass()))
			{
				Cast<AEnemigo>(OtherActor)->RecibirDanio(DanioProyectil);
				Destroy();
			}
			else if (OtherActor->IsA(ATorreta::StaticClass()))
			{
				UGameplayStatics::ApplyDamage(OtherActor, DanioProyectil, GetInstigatorController(), this, UDamageType::StaticClass());
				Destroy();
			}
		}
	}
}