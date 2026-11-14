#include "EnemigoBuilder.h"

FEnemigoBuilder::FEnemigoBuilder() { Config = FConfigEnemigo(); }
FEnemigoBuilder& FEnemigoBuilder::SetTipo(ETipoEnemigo Tipo) { Config.Tipo = Tipo; return *this; }
FEnemigoBuilder& FEnemigoBuilder::SetMalla(const FString& RutaMalla) { Config.MallaRuta = RutaMalla; return *this; }
FEnemigoBuilder& FEnemigoBuilder::SetMaterial(const FString& RutaMaterial) { Config.RutaMaterial = RutaMaterial; return *this; }
FEnemigoBuilder& FEnemigoBuilder::SetEscala(float X, float Y, float Z) { Config.Escala = FVector(X, Y, Z); return *this; }
FEnemigoBuilder& FEnemigoBuilder::SetVida(float Vida) { Config.Vida = Vida; return *this; }

FEnemigoBuilder& FEnemigoBuilder::SetPatron(EPatronMovimiento Patron, FVector Centro, float Velocidad, float RangoDet, float RangoAtq)
{
    Config.Patron = Patron;
    Config.CentroPatron = Centro;
    Config.Velocidad = Velocidad;
    Config.RangoDeteccion = RangoDet;
    Config.RangoAtaque = RangoAtq;
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetFormacion(int32 Indice, int32 Total)
{
    Config.IndiceFormacion = Indice;
    Config.TotalFormacion = Total;
    return *this;
}

AEnemigo* FEnemigoBuilder::Construir(UWorld* World, FVector Location, FRotator Rotation)
{
    if (!World) return nullptr;

    // FORZAMOS EL SPAWN IGNORANDO COLISIONES
    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    AEnemigo* Nuevo = World->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), Location, Rotation, Params);
    if (Nuevo) Nuevo->Configurar(Config);
    return Nuevo;
}