// ============================================================
//  FabricaPlataformas.h
//  PATRON: FACTORY METHOD
// ============================================================
//
//  Esta clase es el CREADOR ABSTRACTO del patrón Factory Method.
//  Define un único método virtual puro: CrearPlataforma().
//
//  Cada subclase concreta (AFabricaTerrestre, AFabricaAcuatica,
//  AFabricaAerea, AFabricaSubterranea) sobreescribe ese método
//  y decide QUÉ tipo concreto de plataforma instanciar.
//
//  Comparación con Abstract Factory:
//    - Factory Method:   1 método virtual → crea 1 tipo de objeto
//    - Abstract Factory: N métodos virtuales → crea N tipos relacionados
// ============================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FabricaPlataformas.generated.h"

class APlataforma;

// CREADOR ABSTRACTO — define el factory method CrearPlataforma()
UCLASS(Abstract)
class AVENTURAUSFX022026L1_API AFabricaPlataformas : public AActor
{
	GENERATED_BODY()

public:
	AFabricaPlataformas();

	// *** FACTORY METHOD *** — subclases concretas lo implementan
	virtual APlataforma* CrearPlataforma(FVector Location, FRotator Rotation)
		PURE_VIRTUAL(AFabricaPlataformas::CrearPlataforma, return nullptr;);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};