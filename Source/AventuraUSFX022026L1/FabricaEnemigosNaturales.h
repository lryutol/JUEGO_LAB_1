// ============================================================
//  FabricaEnemigosNaturales.h
//  PATRON: ABSTRACT FACTORY — Fabrica Concreta #2
// ============================================================
//
//  Implementa AFabricaEnemigos para la FAMILIA NATURAL.
//  Todos sus enemigos usan modelos orgánicos/naturales:
//    - Aéreo:     Halcón (Diluc Falcon)
//    - Acuático:  Pez Naranja
//    - Terrestre: Lobo
// ============================================================

#pragma once

#include "CoreMinimal.h"
#include "FabricaEnemigos.h"
#include "FabricaEnemigosNaturales.generated.h"

// FABRICA CONCRETA #2 de la Abstract Factory de Enemigos
UCLASS()
class AVENTURAUSFX022026L1_API AFabricaEnemigosNaturales : public AFabricaEnemigos
{
	GENERATED_BODY()

public:
	// Implementaciones concretas de los factory methods heredados
	virtual AEnemigo* CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total) override;
	virtual AEnemigo* CrearEnemigoAcuatico(FVector Location, FRotator Rotation) override;
	virtual AEnemigo* CrearEnemigoTerrestre(FVector Location, FRotator Rotation) override;
};