#pragma once

#include "CoreMinimal.h"
#include "FabricaEnemigos.h"
#include "FabricaEnemigosTecnologicos.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API AFabricaEnemigosTecnologicos : public AFabricaEnemigos
{
	GENERATED_BODY()

public:
	virtual AEnemigo* CrearEnemigoAereo(FVector Location, FRotator Rotation) override;
	virtual AEnemigo* CrearEnemigoAcuatico(FVector Location, FRotator Rotation) override;
	virtual AEnemigo* CrearEnemigoTerrestre(FVector Location, FRotator Rotation) override;
};