#pragma once

#include "CoreMinimal.h"
#include "FabricaPlataformas.h"
#include "FabricaAerea.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API AFabricaAerea : public AFabricaPlataformas
{
	GENERATED_BODY()

public:
	virtual APlataforma* CrearPlataforma(FVector Location, FRotator Rotation) override;
};