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
		mallaPlataforma->SetWorldScale3D(FVector(2.0f, 2.0f, 0.2f));
	}

	// Movimiento: Muy lento, flotando (vertical)
	VelocidadAscensor = 0.5f;
	AmplitudAscensor = 150.0f;
	bEsHorizontal = false;
}