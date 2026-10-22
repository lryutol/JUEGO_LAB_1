#include "FabricaEnemigosNaturales.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h"

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAereo(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.0f, 2.0f, 2.0f)
        .SetVida(60.0f)
        .SetMovimiento(FVector(1, 1, 1), FVector(500.0f, 500.0f, 250.0f), FVector(-1500, -1500, 400), FVector(1500, 1500, 1400))
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.5f, 1.0f, 1.0f)
        .SetVida(80.0f)
        .SetMovimiento(FVector(1, 1, 0), FVector(200.0f, 200.0f, 0.0f), FVector(-1200, -1200, 400), FVector(1200, 1200, 600))
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(1.5f, 2.0f, 1.0f)
        .SetVida(100.0f)
        .SetMovimiento(FVector(1, 1, 0), FVector(180.0f, 180.0f, 0.0f), FVector(-1300, -1300, 0), FVector(1300, 1300, 0))
        .Construir(GetWorld(), Location, Rotation);
}