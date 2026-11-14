#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Jefe.generated.h"

class UEstrategiaAtaque;

UCLASS()
class AVENTURAUSFX022026L1_API AJefe : public AEnemigo
{
	GENERATED_BODY()

public:
	AJefe();

	UPROPERTY()
	UEstrategiaAtaque* EstrategiaActual;

	int32 TorretasDestruidas;
	bool bFaseMediaActivada;
	bool bFaseFinalActivada;
	bool bEstaHuyendo;

	void CambiarEstrategia(int32 Fase);

	UFUNCTION()
	void AlDestruirTorreta();

	virtual void RecibirDanio(float Cantidad) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerAtaqueJefe;
	void EjecutarAtaque();
};