#include "PlataformaSubterranea.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaSubterranea::APlataformaSubterranea()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_SUBTERRANEA;

	// NUEVA MALLA SUBTERRÁNEA: SM_Box_8
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SciFi_Props/Models/SM_Box_8.SM_Box_8'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(1.0f, 1.0f, 0.5f)); // Ajusta la escala si es necesario
	}

	// Movimiento: solo sube y baja
	movimientoEjes = FVector(0.0f, 0.0f, 1.0f);
	movimientoLimitesMaximos = FVector(0.0f, 0.0f, 1000.0f);
	movimientoLimitesMinimos = FVector(0.0f, 0.0f, 100.0f);
	movimientoVelocidades = FVector(0.0f, 0.0f, 60.0f);
	movimientoDireccion = FVector(0.0f, 0.0f, FMath::RandBool() ? 1.0f : -1.0f);
}