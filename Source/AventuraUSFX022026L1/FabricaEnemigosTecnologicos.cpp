#include "FabricaEnemigosTecnologicos.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h"

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAereo(FVector Location, FRotator Rotation)
{
    // Dron: Cilindro plano, muy rápido, poca vida
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"))
        .SetEscala(1.5f, 1.5f, 0.4f)
        .SetVida(40.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 1.0f),
            FVector(600.0f, 600.0f, 250.0f),
            FVector(-1800.0f, -1800.0f, 600.0f),
            FVector(1800.0f, 1800.0f, 1400.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    // Submarino: Cilindro grueso, lento pero mucha vida
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"))
        .SetEscala(2.0f, 2.0f, 0.7f)
        .SetVida(120.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 1.0f),
            FVector(200.0f, 200.0f, 100.0f),
            FVector(-1200.0f, -1200.0f, 300.0f),
            FVector(1200.0f, 1200.0f, 800.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    // Tanque: Cubo ancho, lento, mucha vida
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"))
        .SetEscala(3.5f, 2.0f, 1.5f)
        .SetVida(200.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 0.0f),
            FVector(250.0f, 250.0f, 0.0f),
            FVector(-1400.0f, -1400.0f, 0.0f),
            FVector(1400.0f, 1400.0f, 0.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}