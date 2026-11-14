#include "FabricaEnemigosNaturales.h"
#include "Enemigo.h"
#include "EnemigoBuilder.h"

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAereo(FVector Location, FRotator Rotation, int32 Index, int32 Total)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/genshin-impact-diluc-falcon/DilucFalcon.DilucFalcon'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.0f, 2.0f, 2.0f)
        .SetVida(60.0f)
        .SetPatron(EPatronMovimiento::Circulo, Location, 400.0f, 1500.0f, 0.0f)
        .SetFormacion(Index, Total)
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoAcuatico(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/orange-fish/source/fish_3_6_upload.fish_3_6_upload'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.5f, 1.0f, 1.0f)
        .SetVida(80.0f)
        .SetPatron(EPatronMovimiento::Cascada, Location, 350.0f, 1500.0f, 0.0f) // Cascada (Entrar/salir del suelo)
        .Construir(GetWorld(), Location, Rotation);
}

AEnemigo* AFabricaEnemigosNaturales::CrearEnemigoTerrestre(FVector Location, FRotator Rotation)
{
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/low-poly-wolf/source/wolf.wolf'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.0f, 3.0f, 1.0f)
        .SetVida(200.0f)
        .SetPatron(EPatronMovimiento::RutaLineal, Location, 300.0f, 1500.0f, 1000.0f) // RutaLineal
        .Construir(GetWorld(), Location, Rotation);
}