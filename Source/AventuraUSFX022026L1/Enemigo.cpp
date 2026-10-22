#include "Enemigo.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;

	tipoEnemigo = ETipoEnemigo::ENEMIGO_TERRESTRE;

	if (GetMesh()) GetMesh()->SetVisibility(false);

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}

	if (GetCapsuleComponent()) GetCapsuleComponent()->SetCapsuleSize(50.0f, 50.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	mallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	mallaEnemigo->SetStaticMesh(DefaultMesh.Object);
	mallaEnemigo->SetupAttachment(GetCapsuleComponent());

	vidaMaxima = 100.0f;
	vidaActual = 100.0f;
}

void AEnemigo::Configurar(const FConfigEnemigo& Config)
{
	tipoEnemigo = Config.Tipo;

	UStaticMesh* Malla = LoadObject<UStaticMesh>(nullptr, *Config.MallaRuta);
	if (Malla && mallaEnemigo)
	{
		mallaEnemigo->SetStaticMesh(Malla);
		mallaEnemigo->SetWorldScale3D(Config.Escala);
	}

	if (!Config.RutaMaterial.IsEmpty() && mallaEnemigo)
	{
		UMaterialInterface* MaterialCargado = LoadObject<UMaterialInterface>(nullptr, *Config.RutaMaterial);
		if (MaterialCargado)
		{
			mallaEnemigo->SetMaterial(0, MaterialCargado);
		}
	}

	vidaMaxima = Config.Vida;
	vidaActual = Config.Vida;

	movimientoEjes = Config.Ejes;
	movimientoVelocidades = Config.Velocidad;
	movimientoLimitesMaximos = Config.LimitesMax;
	movimientoLimitesMinimos = Config.LimitesMin;
	movimientoDireccion = FVector(
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f
	);
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	vidaActual = vidaMaxima;
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	posicionActual = GetActorLocation();

	if (posicionActual.X >= movimientoLimitesMaximos.X || posicionActual.X <= movimientoLimitesMinimos.X) movimientoDireccion.X *= -1.0f;
	if (posicionActual.Y >= movimientoLimitesMaximos.Y || posicionActual.Y <= movimientoLimitesMinimos.Y) movimientoDireccion.Y *= -1.0f;
	if (posicionActual.Z >= movimientoLimitesMaximos.Z || posicionActual.Z <= movimientoLimitesMinimos.Z) movimientoDireccion.Z *= -1.0f;

	FVector desplazamiento = movimientoDireccion * movimientoVelocidades * movimientoEjes * DeltaTime;
	SetActorLocation(posicionActual + desplazamiento);
}