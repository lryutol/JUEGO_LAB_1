// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AventuraUSFX022026L1GameMode.generated.h"

class APlataforma;
class AEnemigo;
class AInventory;

UCLASS(MinimalAPI)
class AAventuraUSFX022026L1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAventuraUSFX022026L1GameMode();

protected:
	virtual void BeginPlay() override;

private:
	AInventory* Inventory;

public:
	virtual void Tick(float DeltaTime) override;

	// Plataformas
	TArray<APlataforma*> aPlataformas;
	FTimerHandle TimerEliminarPlataforma;
	void EliminarPlataforma();
	int tipoPlataformaActual;

	// Enemigos
	TArray<AEnemigo*> aEnemigos;
	FTimerHandle TimerEliminarEnemigo;
	void EliminarEnemigo();
	int tipoEnemigoActual;
};