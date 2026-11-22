// ============================================================
//  FabricaEnemigosTecnologicos.h
//  PATRON: ABSTRACT FACTORY — Fabrica Concreta #1
// ============================================================
//
//  Implementa AFabricaEnemigos para la FAMILIA TECNOLÓGICA.
//  Todos sus enemigos usan modelos y stats tecnológicos:
//    - Aéreo:     Drone SciFi
//    - Acuático:  Submarino WWII
//    - Terrestre: Tanque
// ============================================================

#pragma once

#include "CoreMinimal.h"
#include "FabricaEnemigos.h"
#include "FabricaEnemigosTecnologicos.generated.h"

// FABRICA CONCRETA #1 de la Abstract Factory de Enemigos
UCLASS()
class AVENTURAUSFX022026L1_API AFabricaEnemigosTecnologicos : public AFabricaEnemigos
{
	GENERATED_BODY()

public:
	// Implementaciones concretas de los factory methods heredados
	virtual AEnemigo* CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total) override;
	virtual AEnemigo* CrearEnemigoAcuatico(FVector Location, FRotator Rotation) override;
	virtual AEnemigo* CrearEnemigoTerrestre(FVector Location, FRotator Rotation) override;
};