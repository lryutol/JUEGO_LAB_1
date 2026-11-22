// ============================================================
//  FabricaArmas.cpp
//  Implementacion de los productos concretos (armas)
// ============================================================

#include "FabricaArmas.h"

// ------------------------------------------------------------
// ArmaLaser
// Arma de corto alcance, daño bajo, cadencia alta
// ------------------------------------------------------------
ArmaLaser::ArmaLaser()
{
    Danio     = 20.0f;
    Velocidad = 3000.0f;
    Cadencia  = 5.0f;   // 5 disparos por segundo
}

void ArmaLaser::Disparar(FVector Origen, FVector Direccion)
{
    // En un juego completo aquí se haría SpawnActor del proyectil laser
    UE_LOG(LogTemp, Log, TEXT("[ArmaLaser] Disparando laser desde (%.0f, %.0f, %.0f)"),
        Origen.X, Origen.Y, Origen.Z);
}

// ------------------------------------------------------------
// ArmaMisil
// Arma de largo alcance, daño alto, cadencia baja
// ------------------------------------------------------------
ArmaMisil::ArmaMisil()
{
    Danio     = 80.0f;
    Velocidad = 1500.0f;
    Cadencia  = 1.0f;   // 1 disparo por segundo
}

void ArmaMisil::Disparar(FVector Origen, FVector Direccion)
{
    UE_LOG(LogTemp, Log, TEXT("[ArmaMisil] Lanzando misil desde (%.0f, %.0f, %.0f)"),
        Origen.X, Origen.Y, Origen.Z);
}

// ------------------------------------------------------------
// ArmaPlasma
// Arma balanceada, daño medio, cadencia media
// ------------------------------------------------------------
ArmaPlasma::ArmaPlasma()
{
    Danio     = 45.0f;
    Velocidad = 2000.0f;
    Cadencia  = 2.5f;   // 2.5 disparos por segundo
}

void ArmaPlasma::Disparar(FVector Origen, FVector Direccion)
{
    UE_LOG(LogTemp, Log, TEXT("[ArmaPlasma] Disparando plasma desde (%.0f, %.0f, %.0f)"),
        Origen.X, Origen.Y, Origen.Z);
}
