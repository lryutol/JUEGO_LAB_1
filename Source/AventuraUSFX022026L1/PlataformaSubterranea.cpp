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
		mallaPlataforma->SetWorldScale3D(FVector(1.0f, 1.0f, 0.5f));
	}

	// Movimiento: Solo sube y baja (vertical)
	VelocidadAscensor = 1.5f;
	AmplitudAscensor = 500.0f;
	bEsHorizontal = false;
}