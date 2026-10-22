#include "PlataformaTerrestre.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaTerrestre::APlataformaTerrestre()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_TERRESTRE;

	// Malla TERRESTRE: cubo (bloque de tierra)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.3f));
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