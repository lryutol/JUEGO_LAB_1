#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

class UStaticMeshComponent;

enum class ETipoPlataforma
{
	PLATAFORMA_AEREA,
	PLATAFORMA_TERRESTRE,
	PLATAFORMA_SUBTERRANEA,
	PLATAFORMA_ACUATICA
};

UCLASS()
class AVENTURAUSFX022026L1_API APlataforma : public AActor
{
	GENERATED_BODY()

public:
	APlataforma();

	ETipoPlataforma tipoPlataforma;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* mallaPlataforma;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Variables para el nuevo movimiento ordenado (Senoidal)
	FVector UbicacionInicial;
	float TiempoPlataforma;
	float VelocidadAscensor;
	float AmplitudAscensor;
	bool bEsHorizontal;
};