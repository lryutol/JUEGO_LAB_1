// ============================================================
//  FabricaEnemigos.h
//  PATRON: ABSTRACT FACTORY
// ============================================================
//
//  Esta clase es la FABRICA ABSTRACTA de enemigos.
//  Define TRES factory methods virtuales puros:
//    - CrearEnemigoAereo()     → produce un enemigo del aire
//    - CrearEnemigoAcuatico()  → produce un enemigo del agua
//    - CrearEnemigoTerrestre() → produce un enemigo de tierra
//
//  Las subclases concretas (AFabricaEnemigosNaturales,
//  AFabricaEnemigosTecnologicos) implementan cada método
//  creando enemigos con estética/stats propios de su familia.
//
//  Resultado: el código que usa AFabricaEnemigos NO necesita
//  saber qué familia está usando; trabaja con la interfaz común.
// ============================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabricaEnemigos.generated.h"

class AEnemigo;

// FABRICA ABSTRACTA — no se puede instanciar directamente (Abstract)
UCLASS(Abstract)
class AVENTURAUSFX022026L1_API AFabricaEnemigos : public AActor
{
	GENERATED_BODY()

public:
	AFabricaEnemigos();

	// --- FACTORY METHODS (virtuales puros) ---
	// Cada familia concreta los implementa con sus propios modelos y stats

	virtual AEnemigo* CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total)
		PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoAereo, return nullptr;);

	virtual AEnemigo* CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
		PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoAcuatico, return nullptr;);

	virtual AEnemigo* CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
		PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoTerrestre, return nullptr;);
};