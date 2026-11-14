#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Torreta.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAlertaTorreta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPeligroFinalizado);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTorretaDestruida);

UCLASS()
class AVENTURAUSFX022026L1_API ATorreta : public AActor
{
	GENERATED_BODY()

public:
	ATorreta();

	UPROPERTY(BlueprintAssignable, Category = "Eventos")
	FOnAlertaTorreta OnAlertaTorreta;

	UPROPERTY(BlueprintAssignable, Category = "Eventos")
	FOnPeligroFinalizado OnPeligroFinalizado;

	UPROPERTY(BlueprintAssignable, Category = "Eventos")
	FOnTorretaDestruida OnTorretaDestruida;

	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	class UStaticMeshComponent* MallaTorreta;

	UPROPERTY(EditAnywhere, Category = "Combate")
	float RangoDeteccion = 2000.0f;

	UPROPERTY(EditAnywhere, Category = "Combate")
	float TiempoEntreDisparos = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Combate")
	float VidaMaxima = 100.0f;

	float VidaActual;

	// NUEVA BANDERA: Indica si la torreta ya fue destruida
	bool bEstaMuerta;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	class APawn* JugadorObjetivo;
	bool bJugadorDetectado;
	FTimerHandle TimerDisparo;

	void DispararAlJugador();
};