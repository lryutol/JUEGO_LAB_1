#include "PlataformaAcuatica.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaAcuatica::APlataformaAcuatica()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_ACUATICA;

	// NUEVA MALLA ACUÁTICA: SM_Box_3
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SciFi_Props/Models/SM_Box_3.SM_Box_3'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.2f)); // Ajusta la escala si es necesario
	}

	// Movimiento: muy lento, flotando
	movimientoEjes = FVector(1.0f, 1.0f, 1.0f);
	movimientoLimitesMaximos = FVector(1200.0f, 1200.0f, 600.0f);
	movimientoLimitesMinimos = FVector(-1200.0f, -1200.0f, 300.0f);
	movimientoVelocidades = FVector(40.0f, 40.0f, 15.0f);
	movimientoDireccion = FVector(
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f,
		FMath::RandBool() ? 1.0f : -1.0f
	);
}