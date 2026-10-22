#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"

class AVENTURAUSFX022026L1_API FEnemigoBuilder
{
private:
    FConfigEnemigo Config;

public:
    FEnemigoBuilder();

    FEnemigoBuilder& SetTipo(ETipoEnemigo Tipo);
    FEnemigoBuilder& SetMalla(const FString& RutaMalla);
    FEnemigoBuilder& SetMaterial(const FString& RutaMaterial);
    FEnemigoBuilder& SetEscala(float X, float Y, float Z);
    FEnemigoBuilder& SetVida(float Vida);
    FEnemigoBuilder& SetMovimiento(FVector Ejes, FVector Velocidad, FVector LimitesMin, FVector LimitesMax);

    AEnemigo* Construir(UWorld* World, FVector Location, FRotator Rotation);
};