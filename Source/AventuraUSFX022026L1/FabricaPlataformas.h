#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabricaPlataformas.generated.h"

class APlataforma;

UCLASS(Abstract)
class AVENTURAUSFX022026L1_API AFabricaPlataformas : public AActor
{
	GENERATED_BODY()

public:
	AFabricaPlataformas();

	virtual APlataforma* CrearPlataforma(FVector Location, FRotator Rotation) PURE_VIRTUAL(AFabricaPlataformas::CrearPlataforma, return nullptr;);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};