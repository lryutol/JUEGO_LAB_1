#include "PlataformaTerrestre.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataformaTerrestre::APlataformaTerrestre()
{
	tipoPlataforma = ETipoPlataforma::PLATAFORMA_TERRESTRE;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SciFi_Props/Models/SM_Box_7.SM_Box_7'"));
	if (MeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(MeshAsset.Object);
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.3f));
	}

	// Movimiento: Lento horizontal
	VelocidadAscensor = 1.0f;
	AmplitudAscensor = 400.0f;
	bEsHorizontal = true;
}