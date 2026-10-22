#include "FabricaTerrestre.h"
#include "PlataformaTerrestre.h"

APlataforma* AFabricaTerrestre::CrearPlataforma(FVector Location, FRotator Rotation)
{
	if (GetWorld())
	{
		return GetWorld()->SpawnActor<APlataformaTerrestre>(Location, Rotation);
	}
	return nullptr;
}