// ============================================================
//  FabricaZona.h
//  PATRON: ABSTRACT FACTORY
// ============================================================
//
//  ¿Qué es Abstract Factory?
//  --------------------------
//  Proporciona una interfaz para crear FAMILIAS de objetos
//  relacionados sin especificar sus clases concretas.
//  A diferencia de Factory Method (que crea UN solo tipo de
//  objeto), Abstract Factory crea VARIOS tipos relacionados.
//
//  Estructura en este archivo:
//
//    Productos abstractos:
//      - AEnemigo      (ya existe en Enemigo.h)
//      - APlataforma   (ya existe en Plataforma.h)
//
//    Fábrica abstracta:  FabricaZona
//      - CrearEnemigoPrincipal()   <-- Factory Method 1
//      - CrearPlataformaZona()     <-- Factory Method 2
//
//    Fábricas concretas (una por bioma):
//      - FabricaZonaBosque     → enemigo lobo + plataforma terrestre
//      - FabricaZonaMarina     → enemigo pez  + plataforma acuática
//      - FabricaZonaAerea      → enemigo drone + plataforma aérea
//      - FabricaZonaSubterranea→ enemigo tanque + plataforma subterránea
//
//  DIFERENCIA CON FACTORY METHOD:
//    Factory Method: una sola familia, un solo método virtual.
//    Abstract Factory: múltiples familias, varios métodos virtuales.
//
// ============================================================

#pragma once

#include "CoreMinimal.h"
#include "Enemigo.h"
#include "Plataforma.h"

// Declaraciones anticipadas (evitar includes circulares)
class APlataformaTerrestre;
class APlataformaAcuatica;
class APlataformaAerea;
class APlataformaSubterranea;

// ------------------------------------------------------------
// FABRICA ABSTRACTA: FabricaZona
//
// Define la interfaz con dos Factory Methods:
//   1) CrearEnemigoPrincipal()  → produce un AEnemigo
//   2) CrearPlataformaZona()    → produce una APlataforma
//
// Ambos son virtuales puros: cada bioma los implementa a su modo.
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaZona
{
public:
    virtual ~FabricaZona() {}

    // Factory Method 1: crea el enemigo característico de esta zona
    virtual AEnemigo* CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) = 0;

    // Factory Method 2: crea la plataforma característica de esta zona
    virtual APlataforma* CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) = 0;

    // Nombre del bioma (útil para logs y depuración)
    virtual FString ObtenerNombreZona() const = 0;

    // Método de alto nivel: inicializa la zona completa.
    // Usa los dos factory methods sin saber qué se crea exactamente.
    void InicializarZona(UWorld* Mundo, FVector UbicacionEnemigo, FVector UbicacionPlataforma)
    {
        UE_LOG(LogTemp, Log, TEXT("[FabricaZona] Creando zona: %s"), *ObtenerNombreZona());

        AEnemigo*    enemigo    = CrearEnemigoPrincipal(Mundo, UbicacionEnemigo,    FRotator::ZeroRotator);
        APlataforma* plataforma = CrearPlataformaZona  (Mundo, UbicacionPlataforma, FRotator::ZeroRotator);

        if (enemigo)
            UE_LOG(LogTemp, Log, TEXT("  -> Enemigo creado en zona %s"),    *ObtenerNombreZona());
        if (plataforma)
            UE_LOG(LogTemp, Log, TEXT("  -> Plataforma creada en zona %s"), *ObtenerNombreZona());
    }
};

// ------------------------------------------------------------
// FABRICA CONCRETA 1: Zona Bosque (enemigos naturales terrestres)
// Crea: lobo (enemigo) + plataforma terrestre
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaZonaBosque : public FabricaZona
{
public:
    virtual AEnemigo* CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual APlataforma* CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual FString ObtenerNombreZona() const override { return TEXT("Bosque"); }
};

// ------------------------------------------------------------
// FABRICA CONCRETA 2: Zona Marina (enemigos acuáticos)
// Crea: pez (enemigo) + plataforma acuática
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaZonaMarina : public FabricaZona
{
public:
    virtual AEnemigo* CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual APlataforma* CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual FString ObtenerNombreZona() const override { return TEXT("Marina"); }
};

// ------------------------------------------------------------
// FABRICA CONCRETA 3: Zona Aérea (enemigos tecnológicos aéreos)
// Crea: drone (enemigo) + plataforma aérea
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaZonaAerea : public FabricaZona
{
public:
    virtual AEnemigo* CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual APlataforma* CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual FString ObtenerNombreZona() const override { return TEXT("Aerea"); }
};

// ------------------------------------------------------------
// FABRICA CONCRETA 4: Zona Subterránea (enemigos tecnológicos terrestres)
// Crea: tanque (enemigo) + plataforma subterránea
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaZonaSubterranea : public FabricaZona
{
public:
    virtual AEnemigo* CrearEnemigoPrincipal(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual APlataforma* CrearPlataformaZona(UWorld* Mundo, FVector Ubicacion, FRotator Rotacion) override;
    virtual FString ObtenerNombreZona() const override { return TEXT("Subterranea"); }
};
