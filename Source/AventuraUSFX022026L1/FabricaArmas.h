// ============================================================
//  FabricaArmas.h
//  PATRON: FACTORY METHOD
// ============================================================
//
//  ¿Qué es Factory Method?
//  -----------------------
//  Define una interfaz para crear un objeto, pero deja que las
//  subclases decidan qué clase concreta instanciar.
//  El creador (FabricaArmas) tiene un método virtual puro
//  "CrearArma()" que cada subclase implementa a su manera.
//
//  Estructura en este archivo:
//
//    Producto abstracto:   Arma
//    Productos concretos:  ArmaLaser, ArmaMisil, ArmaPlasma
//    Creador abstracto:    FabricaArmas  <-- define CrearArma()
//    Creadores concretos:  FabricaLaser, FabricaMisil, FabricaPlasma
//
// ============================================================

#pragma once

#include "CoreMinimal.h"

// ------------------------------------------------------------
// PRODUCTO ABSTRACTO: Arma
// Todos los tipos de arma deben cumplir esta interfaz.
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API Arma
{
public:
    virtual ~Arma() {}

    // Cada arma concreta implementa cómo dispara
    virtual void Disparar(FVector Origen, FVector Direccion) = 0;

    // Información descriptiva del arma (útil para depuración/HUD)
    virtual FString ObtenerNombre() const = 0;

    float Danio;        // Daño por disparo
    float Velocidad;    // Velocidad del proyectil
    float Cadencia;     // Disparos por segundo
};

// ------------------------------------------------------------
// PRODUCTOS CONCRETOS
// Cada uno implementa un tipo de arma diferente.
// ------------------------------------------------------------

class AVENTURAUSFX022026L1_API ArmaLaser : public Arma
{
public:
    ArmaLaser();
    virtual void Disparar(FVector Origen, FVector Direccion) override;
    virtual FString ObtenerNombre() const override { return TEXT("Laser"); }
};

class AVENTURAUSFX022026L1_API ArmaMisil : public Arma
{
public:
    ArmaMisil();
    virtual void Disparar(FVector Origen, FVector Direccion) override;
    virtual FString ObtenerNombre() const override { return TEXT("Misil"); }
};

class AVENTURAUSFX022026L1_API ArmaPlasma : public Arma
{
public:
    ArmaPlasma();
    virtual void Disparar(FVector Origen, FVector Direccion) override;
    virtual FString ObtenerNombre() const override { return TEXT("Plasma"); }
};

// ------------------------------------------------------------
// CREADOR ABSTRACTO: FabricaArmas
//
// Declara el Factory Method "CrearArma()" como virtual puro.
// También puede tener lógica común que usa CrearArma().
// ------------------------------------------------------------
class AVENTURAUSFX022026L1_API FabricaArmas
{
public:
    virtual ~FabricaArmas() {}

    // *** FACTORY METHOD *** — subclases lo implementan
    virtual Arma* CrearArma() = 0;

    // Método de "alto nivel" que usa el factory method.
    // El creador no sabe qué tipo de arma se crea; solo la usa.
    Arma* ObtenerArmaLista()
    {
        Arma* nueva = CrearArma();         // llama al factory method
        UE_LOG(LogTemp, Log, TEXT("[FabricaArmas] Arma creada: %s | Daño: %.1f"), *nueva->ObtenerNombre(), nueva->Danio);
        return nueva;
    }
};

// ------------------------------------------------------------
// CREADORES CONCRETOS
// Cada uno sobreescribe CrearArma() y decide qué instanciar.
// ------------------------------------------------------------

class AVENTURAUSFX022026L1_API FabricaLaser : public FabricaArmas
{
public:
    virtual Arma* CrearArma() override
    {
        return new ArmaLaser();
    }
};

class AVENTURAUSFX022026L1_API FabricaMisil : public FabricaArmas
{
public:
    virtual Arma* CrearArma() override
    {
        return new ArmaMisil();
    }
};

class AVENTURAUSFX022026L1_API FabricaPlasma : public FabricaArmas
{
public:
    virtual Arma* CrearArma() override
    {
        return new ArmaPlasma();
    }
};
