#include "FabricaEnemigosTecnologicos.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h"

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAereo(FVector Location, FRotator Rotation)
{
    // DRON
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/scifi-drone/DroneSciFi.DroneSciFi'"))
        .SetEscala(0.5f, 0.5f, 0.5f) // Si el dron sale muy grande, baja esto a 0.05f. Si sale chico, sube a 0.2f
        .SetVida(40.0f)
        .SetMovimiento(FVector(1, 1, 1), FVector(600.0f, 600.0f, 250.0f), FVector(-1800, -1800, 600), FVector(1800, 1800, 1400))
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    // SUBMARINO
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/wwii-submarine/source/WWII_Submarine.WWII_Submarine'"))
        .SetEscala(0.2f, 0.2f, 0.2f) // Ajusta si es necesario
        .SetVida(120.0f)
        .SetMovimiento(FVector(1, 1, 1), FVector(200.0f, 200.0f, 100.0f), FVector(-1200, -1200, 300), FVector(1200, 1200, 800))
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    // TANQUE
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/tank/LightTank_Preview_.LightTank_Preview_'"))
        .SetEscala(20.1f, 20.1f, 20.1f)
        .SetVida(200.0f)
        .SetMovimiento(FVector(1, 1, 0), FVector(250.0f, 250.0f, 0.0f), FVector(-1400, -1400, 0), FVector(1400, 1400, 0))
        .Construir(GetWorld(), Location, Rotation);
}