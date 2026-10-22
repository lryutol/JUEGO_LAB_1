#include "PlataformaSubterranea.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaSubterranea::APlataformaSubterranea()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_SUBTERRANEA;

	// Malla SUBTERRÁNEA: cono (taladro)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(1.0f, 1.0f, 0.5f));
	}

	// Movimiento: solo sube y baja
	movimientoEjes = FVector(0.0f, 0.0f, 1.0f);
	movimientoLimitesMaximos = FVector(0.0f, 0.0f, 1000.0f);
	movimientoLimitesMinimos = FVector(0.0f, 0.0f, 100.0f);
	movimientoVelocidades = FVector(0.0f, 0.0f, 60.0f);
	movimientoDireccion = FVector(0.0f, 0.0f, FMath::RandBool() ? 1.0f : -1.0f);
}