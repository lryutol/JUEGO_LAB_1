#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AventuraUSFX022026L1GameMode.generated.h"

class AFachadaJuego;

UCLASS(MinimalAPI)
class AAventuraUSFX022026L1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAventuraUSFX022026L1GameMode();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AFachadaJuego* MiFachada;

	FTimerHandle TimerEliminarPlataforma;
	FTimerHandle TimerEliminarEnemigo;

	void EliminarPlataforma();
	void EliminarEnemigo();
};