#pragma once

#include "CoreMinimal.h"
#include "FabricaPlataformas.h"
#include "FabricaTerrestre.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API AFabricaTerrestre : public AFabricaPlataformas
{
	GENERATED_BODY()

public:
	virtual APlataforma* CrearPlataforma(FVector Location, FRotator Rotation) override;
};