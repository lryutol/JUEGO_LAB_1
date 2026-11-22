// ============================================================
//  FabricaZona.cpp
//  Implementacion de las fabricas concretas de zona
//  PATRON: ABSTRACT FACTORY
// ============================================================

#include "FabricaZona.h"
#include "EnemigoBuilder.h"
#include "PlataformaTerrestre.h"
#include "PlataformaAcuatica.h"
#include "PlataformaAerea.h"
#include "PlataformaSubterranea.h"

// ============================================================
// FABRICA CONCRETA 1: Zona Bosque
// ============================================================

AEnemigo* FabricaZonaBosque::CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    // Enemigo natural terrestre: lobo
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/low-poly-wolf/source/wolf.wolf'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.0f, 3.0f, 1.0f)
        .SetVida(200.0f)
        .SetPatron(EPatronMovimiento::RutaLineal, Ubicacion, 300.0f, 1500.0f, 1000.0f)
        .Construir(Mundo, Ubicacion, Rotacion);
}

APlataforma* FabricaZonaBosque::CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    if (!Mundo) return nullptr;
    return Mundo->SpawnActor<APlataformaTerrestre>(Ubicacion, Rotacion);
}

// ============================================================
// FABRICA CONCRETA 2: Zona Marina
// ============================================================

AEnemigo* FabricaZonaMarina::CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    // Enemigo natural acuático: pez
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_ACUATICO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/orange-fish/source/fish_3_6_upload.fish_3_6_upload'"))
        .SetMaterial(TEXT("MaterialInstanceConstant'/Game/StarSparrow/Materials/MI_StarSparrow_Green.MI_StarSparrow_Green'"))
        .SetEscala(2.5f, 1.0f, 1.0f)
        .SetVida(80.0f)
        .SetPatron(EPatronMovimiento::Cascada, Ubicacion, 350.0f, 1500.0f, 0.0f)
        .Construir(Mundo, Ubicacion, Rotacion);
}

APlataforma* FabricaZonaMarina::CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    if (!Mundo) return nullptr;
    return Mundo->SpawnActor<APlataformaAcuatica>(Ubicacion, Rotacion);
}

// ============================================================
// FABRICA CONCRETA 3: Zona Aérea
// ============================================================

AEnemigo* FabricaZonaAerea::CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    // Enemigo tecnológico aéreo: drone
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_AEREO)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/scifi-drone/DroneSciFi.DroneSciFi'"))
        .SetEscala(0.5f, 0.5f, 0.5f)
        .SetVida(40.0f)
        .SetPatron(EPatronMovimiento::Circulo, Ubicacion, 400.0f, 1500.0f, 0.0f)
        .SetFormacion(0, 1)
        .Construir(Mundo, Ubicacion, Rotacion);
}

APlataforma* FabricaZonaAerea::CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    if (!Mundo) return nullptr;
    return Mundo->SpawnActor<APlataformaAerea>(Ubicacion, Rotacion);
}

// ============================================================
// FABRICA CONCRETA 4: Zona Subterránea
// ============================================================

AEnemigo* FabricaZonaSubterranea::CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    // Enemigo tecnológico terrestre: tanque
    return FEnemigoBuilder()
        .SetTipo(ETipoEnemigo::ENEMIGO_TERRESTRE)
        .SetMalla(TEXT("StaticMesh'/Game/modelos/tank/LightTank_Preview_.LightTank_Preview_'"))
        .SetEscala(20.1f, 20.1f, 20.1f)
        .SetVida(200.0f)
        .SetPatron(EPatronMovimiento::RutaLineal, Ubicacion, 300.0f, 1500.0f, 1000.0f)
        .Construir(Mundo, Ubicacion, Rotacion);
}

APlataforma* FabricaZonaSubterranea::CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion)
{
    if (!Mundo) return nullptr;
    return Mundo->SpawnActor<APlataformaSubterranea>(Ubicacion, Rotacion);
}
