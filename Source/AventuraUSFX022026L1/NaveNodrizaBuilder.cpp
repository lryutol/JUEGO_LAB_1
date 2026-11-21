#include "NaveNodrizaBuilder.h"
#include "NaveNodriza.h"
#include "Engine/StaticMesh.h"

void FNaveNodrizaBuilder::EnsamblarCasco(UStaticMesh* Malla, FVector Escala)
{
	CascoMalla = Malla;
	CascoEscala = Escala;
}

void FNaveNodrizaBuilder::EnsamblarMotores(UStaticMesh* Malla, FVector Escala)
{
	MotoresMalla = Malla;
	MotoresEscala = Escala;
}

void FNaveNodrizaBuilder::EnsamblarTorretas(UStaticMesh* Malla, FVector Escala)
{
	TorretasMalla = Malla;
	TorretasEscala = Escala;
}

ANaveNodriza* FNaveNodrizaBuilder::Construir(UWorld* World, FVector Location, FRotator Rotation)
{
	if (!World) return nullptr;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ANaveNodriza* Nave = World->SpawnActor<ANaveNodriza>(ANaveNodriza::StaticClass(), Location, Rotation, Params);

	if (Nave)
	{
		// Aquí le decimos a la Nave que ensamble sus partes visuales
		Nave->EnsamblarPartes(CascoMalla, CascoEscala, MotoresMalla, MotoresEscala, TorretasMalla, TorretasEscala);
	}
	return Nave;
}