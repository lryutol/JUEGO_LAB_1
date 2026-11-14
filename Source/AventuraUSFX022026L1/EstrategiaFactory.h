#pragma once
#include "CoreMinimal.h"
#include "EstrategiaAtaque.h"

class AVENTURAUSFX022026L1_API FEstrategiaFactory
{
public:
	static UEstrategiaAtaque* CrearEstrategia(int32 Fase);
};