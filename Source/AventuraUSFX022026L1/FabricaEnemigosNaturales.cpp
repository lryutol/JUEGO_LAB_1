#include "FabricaEnemigosNaturales.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h" // Incluimos el Builder

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAereo(FVector Location, FRotator Rotation)
{
    // El Halcón: Rápido, cono, mucha altura
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"))
        .SetEscala(2.0f, 2.0f, 2.0f)
        .SetVida(60.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 1.0f),
            FVector(500.0f, 500.0f, 250.0f),
            FVector(-1500.0f, -1500.0f, 400.0f),
            FVector(1500.0f, 1500.0f, 1400.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    // El Pez: Esfera alargada, movimiento horizontal
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"))
        .SetEscala(2.5f, 1.0f, 1.0f)
        .SetVida(80.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 0.0f),
            FVector(200.0f, 200.0f, 0.0f),
            FVector(-1200.0f, -1200.0f, 400.0f),
            FVector(1200.0f, 1200.0f, 600.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    // El Lobo: Cubo robusto, movimiento por el suelo
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"))
        .SetEscala(1.5f, 2.0f, 1.0f)
        .SetVida(100.0f)
        .SetMovimiento(
            FVector(1.0f, 1.0f, 0.0f),
            FVector(180.0f, 180.0f, 0.0f),
            FVector(-1300.0f, -1300.0f, 0.0f),
            FVector(1300.0f, 1300.0f, 0.0f)
        )
        .Construir(GetWorld(), Location, Rotation);
}