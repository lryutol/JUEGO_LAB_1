#include "NaveNodriza.h"
#include "EstadoNaveNodriza.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ANaveNodriza::ANaveNodriza()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Raiz"));
}

void ANaveNodriza::BeginPlay()
{
	Super::BeginPlay();
	JugadorObjetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	CambiarEstado(NewObject<UEstadoNaveNormal>(this));
}

// AQUÍ VEMOS EL ENSAMBLAJE DEL BUILDER EN ACCIÓN
void ANaveNodriza::EnsamblarPartes(UStaticMesh* Casco, FVector EscalaCasco, UStaticMesh* Motor, FVector EscalaMotor, UStaticMesh* Torreta, FVector EscalaTorreta)
{
	if (Casco)
	{
		CompCasco = NewObject<UStaticMeshComponent>(this);
		CompCasco->RegisterComponent();
		CompCasco->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CompCasco->SetStaticMesh(Casco);
		CompCasco->SetWorldScale3D(EscalaCasco);
	}
	if (Motor)
	{
		CompMotores = NewObject<UStaticMeshComponent>(this);
		CompMotores->RegisterComponent();
		CompMotores->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CompMotores->SetStaticMesh(Motor);
		CompMotores->SetWorldScale3D(EscalaMotor);
		CompMotores->SetRelativeLocation(FVector(-500.0f, 0.0f, 0.0f)); // Atrás
	}
	if (Torreta)
	{
		CompTorretas = NewObject<UStaticMeshComponent>(this);
		CompTorretas->RegisterComponent();
		CompTorretas->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		CompTorretas->SetStaticMesh(Torreta);
		CompTorretas->SetWorldScale3D(EscalaTorreta);
		CompTorretas->SetRelativeLocation(FVector(300.0f, 0.0f, 200.0f)); // Adelante y arriba
	}
}

void ANaveNodriza::CambiarEstado(UEstadoNaveNodriza* NuevoEstado)
{
	if (EstadoActual) EstadoActual->ConditionalBeginDestroy();
	EstadoActual = NuevoEstado;
	if (EstadoActual) EstadoActual->Entrar(this);
}

float ANaveNodriza::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	VidaActual -= DamageAmount;

	// TRANSICIONES DEL STATE SEGÚN LA VIDA
	if (VidaActual <= (VidaMaxima * 0.5f) && !EstadoActual->IsA(UEstadoNaveAveriada::StaticClass()) && VidaActual > (VidaMaxima * 0.1f))
	{
		CambiarEstado(NewObject<UEstadoNaveAveriada>(this));
	}
	else if (VidaActual <= (VidaMaxima * 0.1f) && !EstadoActual->IsA(UEstadoNaveCritica::StaticClass()))
	{
		CambiarEstado(NewObject<UEstadoNaveCritica>(this));
	}

	if (VidaActual <= 0.0f) Destroy();
	return DamageAmount;
}

// EL TICK SOLO DELEGA AL ESTADO
void ANaveNodriza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EstadoActual)
	{
		EstadoActual->Tick(this, DeltaTime);
	}
}