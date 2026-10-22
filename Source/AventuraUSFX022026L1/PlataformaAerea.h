#pragma once

#include "CoreMinimal.h"
#include "Plataforma.h"
#include "PlataformaAerea.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API APlataformaAerea : public APlataforma
{
	GENERATED_BODY()

public:
	APlataformaAerea();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	int numeroPaso;
};