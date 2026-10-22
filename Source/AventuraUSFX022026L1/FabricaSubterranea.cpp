#include "FabricaSubterranea.h"
#include "PlataformaSubterranea.h"

APlataforma* AFabricaSubterranea::CrearPlataforma(FVector Location, FRotator Rotation)
{
	if (GetWorld())
	{
		return GetWorld()->SpawnActor<APlataformaSubterranea>(Location, Rotation);
	}
	return nullptr;
}