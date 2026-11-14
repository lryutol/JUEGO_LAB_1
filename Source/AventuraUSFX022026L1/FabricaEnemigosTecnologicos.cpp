#include "FabricaEnemigosTecnologicos.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h"

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/scifi-drone/DroneSciFi.DroneSciFi'"))
        .SetEscala(0.5f, 0.5f, 0.5f)
        .SetVida(40.0f)
        .SetPatron(EPatronMovimiento::Circulo, Location, 400.0f, 1500.0f, 0.0f)
        .SetFormacion(Index, Total)
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/wwii-submarine/source/WWII_Submarine.WWII_Submarine'"))
        .SetEscala(0.2f, 0.2f, 0.2f)
        .SetVida(120.0f)
        .SetPatron(EPatronMovimiento::Aleatorio, Location, 350.0f, 1500.0f, 0.0f)
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosTecnologicos::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/tank/LightTank_Preview_.LightTank_Preview_'"))
        .SetEscala(20.1f, 20.1f, 20.1f)
        .SetVida(200.0f)
        .SetPatron(EPatronMovimiento::RutaLineal, Location, 300.0f, 1500.0f, 1000.0f) // RutaLineal
        .Construir(GetWorld(), Location, Rotation);
}