#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabricaEnemigos.generated.h"

class AEnemigo;

UCLASS(Abstract)
class AVENTURAUSFX022026L1_API AFabricaEnemigos : public AActor
{
	GENERATED_BODY()

public:
	AFabricaEnemigos();

	virtual AEnemigo* CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total) PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoAereo, return nullptr;);
	virtual AEnemigo* CrearEnemigoAcuatico(FVector Location, FRotator Rotation) PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoAcuatico, return nullptr;);
	virtual AEnemigo* CrearEnemigoTerrestre(FVector Location, FRotator Rotation) PURE_VIRTUAL(AFabricaEnemigos::CrearEnemigoTerrestre, return nullptr;);
};