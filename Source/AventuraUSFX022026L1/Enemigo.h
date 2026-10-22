#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

class UStaticMeshComponent;

enum class ETipoEnemigo
{
	ENEMIGO_TERRESTRE,
	ENEMIGO_ACUATICO,
	ENEMIGO_AEREO
};

struct FConfigEnemigo
{
	ETipoEnemigo Tipo = ETipoEnemigo::ENEMIGO_TERRESTRE;
	FString MallaRuta = TEXT("");
	FString RutaMaterial = TEXT("");
	FVector Escala = FVector(1.0f, 1.0f, 1.0f);
	float Vida = 100.0f;
	FVector Ejes = FVector(1.0f, 1.0f, 0.0f);
	FVector Velocidad = FVector(100.0f, 100.0f, 0.0f);
	FVector LimitesMin = FVector(-1000.0f, -1000.0f, 0.0f);
	FVector LimitesMax = FVector(1000.0f, 1000.0f, 0.0f);
};

UCLASS()
class AVENTURAUSFX022026L1_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemigo();

	ETipoEnemigo tipoEnemigo;
	UStaticMeshComponent* mallaEnemigo;

	void Configurar(const FConfigEnemigo& Config);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FVector movimientoEjes = FVector(0.0f, 0.0f, 0.0f);
	FVector movimientoLimitesMaximos = FVector(0.0f, 0.0f, 0.0f);
	FVector movimientoLimitesMinimos = FVector(0.0f, 0.0f, 0.0f);
	FVector movimientoVelocidades = FVector(0.0f, 0.0f, 0.0f);
	FVector movimientoDireccion = FVector(0.0f, 0.0f, 0.0f);
	FVector posicionActual = FVector(0.0f, 0.0f, 0.0f);

	float vidaMaxima;
	float vidaActual;
};