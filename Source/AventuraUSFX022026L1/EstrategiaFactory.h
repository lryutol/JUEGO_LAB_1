// ============================================================
//  EstrategiaFactory.h
//  PATRON: FACTORY METHOD (variante estática / simple)
// ============================================================
//
//  Esta es la forma más simple de Factory Method:
//  un método estático que recibe un parámetro y decide
//  qué objeto concreto crear y devolver.
//
//  Se usa para crear la UEstrategiaAtaque correcta según
//  la fase del jefe final. El código del jefe no necesita
//  saber qué estrategia concreta se usa; solo llama a
//  FEstrategiaFactory::CrearEstrategia(fase).
//
//  Fase 1 → UEAtaqueBasico
//  Fase 2 → UEAtaquePesado
//  Fase 3 → UEAtaqueInvocar
//  Fase 4 → UEAtaqueAbanico
//  Fase 5 → UEAtaqueRed
// ============================================================

#pragma once
#include "CoreMinimal.h"
#include "EstrategiaAtaque.h"

// CREADOR (versión estática del Factory Method)
class AVENTURAUSFX022026L1_API FEstrategiaFactory
{
public:
	// *** FACTORY METHOD *** — decide qué estrategia crear según la fase
	static UEstrategiaAtaque* CrearEstrategia(int32 Fase);
};