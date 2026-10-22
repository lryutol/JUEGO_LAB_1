#include "PlataformaAerea.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaAerea::APlataformaAerea()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_AEREA;

	// NUEVA MALLA AÉREA: SM_Box_5
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SciFi_Props/Models/SM_Box_5.SM_Box_5'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.5f)); // Ajusta la escala si es necesario
	}

	// Movimiento: rápido, en las 3 dimensiones
	movimientoEjes = FVector(1.0f, 1.0f, 1.0f);
	movimientoLimitesMaximos = FVector(1500.0f, 1500.0f, 1200.0f);
	movimientoLimitesMinimos = FVector(-1500.0f, -1500.0f, 200.0f);
	movimientoVelocidades = FVector(300.0f, 300.0f, 200.0f);
	movimientoDireccion = FVector(
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f
	);

	numeroPaso = 0;
}

void APlataformaAerea::BeginPlay()
{
	Super::BeginPlay();
}

void APlataformaAerea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}