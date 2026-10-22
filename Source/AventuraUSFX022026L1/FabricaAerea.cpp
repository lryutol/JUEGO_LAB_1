#include "FabricaAerea.h"
#include "PlataformaAerea.h"

APlataforma* AFabricaAerea::CrearPlataforma(FVector Location, FRotator Rotation)
{
	if (GetWorld())
	{
		return GetWorld()->SpawnActor<APlataformaAerea>(Location, Rotation);
	}
	return nullptr;
}