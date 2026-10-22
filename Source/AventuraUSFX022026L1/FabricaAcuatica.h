#pragma once

#include "CoreMinimal.h"
#include "FabricaPlataformas.h"
#include "FabricaAcuatica.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API AFabricaAcuatica : public AFabricaPlataformas
{
	GENERATED_BODY()

public:
	virtual APlataforma* CrearPlataforma(FVector Location, FRotator Rotation) override;
};