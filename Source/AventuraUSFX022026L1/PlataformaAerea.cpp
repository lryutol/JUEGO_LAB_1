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
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.5f));
	}

	// Movimiento: Rápido, vaivén horizontal
	VelocidadAscensor = 3.0f;
	AmplitudAscensor = 600.0f;
	bEsHorizontal = true;
}

// AQUÍ ESTÁN LAS FUNCIONES QUE TE FALTABAN
void APlataformaAerea::BeginPlay()
{
	Super::BeginPlay();
}

void APlataformaAerea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}