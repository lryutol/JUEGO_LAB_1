#pragma once

#include "CoreMinimal.h"

class ANaveNodriza;
class UStaticMesh;

class AVENTURAUSFX022026L1_API FNaveNodrizaBuilder
{
public:
	// Métodos para ensamblar cada pieza de la nave
	void EnsamblarCasco(UStaticMesh* Malla, FVector Escala);
	void EnsamblarMotores(UStaticMesh* Malla, FVector Escala);
	void EnsamblarTorretas(UStaticMesh* Malla, FVector Escala);

	// Retorna el objeto complejo construido
	ANaveNodriza* Construir(UWorld* World, FVector Location, FRotator Rotation);

private:
	UStaticMesh* CascoMalla = nullptr;
	FVector CascoEscala;

	UStaticMesh* MotoresMalla = nullptr;
	FVector MotoresEscala;

	UStaticMesh* TorretasMalla = nullptr;
	FVector TorretasEscala;
};