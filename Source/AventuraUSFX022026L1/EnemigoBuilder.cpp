#include "EnemigoBuilder.h"

FEnemigoBuilder::FEnemigoBuilder()
{
    Config = FConfigEnemigo();
}

FEnemigoBuilder& FEnemigoBuilder::SetTipo(ETipoEnemigo Tipo)
{
    Config.Tipo = Tipo;
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetMalla(const FString& RutaMalla)
{
    Config.MallaRuta = RutaMalla;
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetMaterial(const FString& RutaMaterial)
{
    Config.RutaMaterial = RutaMaterial;
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetEscala(float X, float Y, float Z)
{
    Config.Escala = FVector(X, Y, Z);
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetVida(float Vida)
{
    Config.Vida = Vida;
    return *this;
}

FEnemigoBuilder& FEnemigoBuilder::SetMovimiento(FVector Ejes, FVector Velocidad, FVector LimitesMin, FVector LimitesMax)
{
    Config.Ejes = Ejes;
    Config.Velocidad = Velocidad;
    Config.LimitesMin = LimitesMin;
    Config.LimitesMax = LimitesMax;
    return *this;
}

AEnemigo* FEnemigoBuilder::Construir(UWorld* World, FVector Location, FRotator Rotation)
{
    if (!World) return nullptr;

    AEnemigo* Nuevo = World->SpawnActor<AEnemigo>(Location, Rotation);
    if (Nuevo)
    {
        Nuevo->Configurar(Config);
    }
    return Nuevo;
}