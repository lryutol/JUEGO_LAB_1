#include "PlataformaTerrestre.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaTerrestre::APlataformaTerrestre()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_TERRESTRE;

	// MALLA TERRESTRE: SM_Box_7
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SciFi_Props/Models/SM_Box_7.SM_Box_7'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.3f)); // Ajusta la escala si es necesario
	}

	// Movimiento: lento, solo en el plano X/Y
	movimientoEjes = FVector(1.0f, 1.0f, 0.0f);
	movimientoLimitesMaximos = FVector(1500.0f, 1500.0f, 0.0f);
	movimientoLimitesMinimos = FVector(-1500.0f, -1500.0f, 0.0f);
	movimientoVelocidades = FVector(80.0f, 80.0f, 0.0f);
	movimientoDireccion = FVector(
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f,
		0.0f
	);
}