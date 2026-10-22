#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h" // Para usar FConfigEnemigo y ETipoEnemigo

// Clase pura de C++ para construir enemigos paso a paso
class AVENTURAUSFX022026L1_API FEnemigoBuilder
{
private:
    FConfigEnemigo Config;

public:
    FEnemigoBuilder();

    // Métodos paso a paso (Devuelven *this para poder encadenar con puntos)
    FEnemigoBuilder& SetTipo(ETipoEnemigo Tipo);
    FEnemigoBuilder& SetMalla(const FString& RutaMalla);
    FEnemigoBuilder& SetEscala(float X, float Y, float Z);
    FEnemigoBuilder& SetVida(float Vida);
    FEnemigoBuilder& SetMovimiento(FVector Ejes, FVector Velocidad, FVector LimitesMin, FVector LimitesMax);

    // Método final que construye el enemigo
    AEnemigo* Construir(UWorld* World, FVector Location, FRotator Rotation);
};