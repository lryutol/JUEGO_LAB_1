#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FachadaJuego.generated.h"

class APlataforma;
class AEnemigo;

UCLASS()
class AVENTURAUSFX022026L1_API AFachadaJuego : public AActor
{
	GENERATED_BODY()

public:
	AFachadaJuego();

	void InicializarMundo(int32 DronesTechPorEsquina, int32 DronesNatPorEsquina, int32 CantidadAcuaticos, int32 NumGruposTanques, int32 NumGruposLobos);

	void EliminarSiguientePlataforma();
	void EliminarSiguienteEnemigo();

protected:
	virtual void BeginPlay() override;

private:
	TArray<APlataforma*> aPlataformas;
	TArray<AEnemigo*> aEnemigos;
	int32 tipoPlataformaActual = 0;
	int32 tipoEnemigoActual = 0;
};