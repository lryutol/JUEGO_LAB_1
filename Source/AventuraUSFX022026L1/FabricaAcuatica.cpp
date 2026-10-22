#include "FabricaAcuatica.h"
#include "PlataformaAcuatica.h"

APlataforma* AFabricaAcuatica::CrearPlataforma(FVector Location, FRotator Rotation)
{
	if (GetWorld())
	{
		return GetWorld()->SpawnActor<APlataformaAcuatica>(Location, Rotation);
	}
	return nullptr;
}