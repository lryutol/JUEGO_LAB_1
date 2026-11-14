#include "EstrategiaFactory.h"

UEstrategiaAtaque* FEstrategiaFactory::CrearEstrategia(int32 Fase)
{
	switch (Fase)
	{
	case 1: return NewObject<UEAtaqueBasico>();
	case 2: return NewObject<UEAtaquePesado>();
	case 3: return NewObject<UEAtaqueInvocar>();
	case 4: return NewObject<UEAtaqueAbanico>();
	case 5: return NewObject<UEAtaqueRed>();
	default: return NewObject<UEAtaqueBasico>();
	}
}