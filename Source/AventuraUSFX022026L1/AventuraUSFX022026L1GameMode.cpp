#include "AventuraUSFX022026L1GameMode.h"
#include "AventuraUSFX022026L1Pawn.h"
#include "Plataforma.h"
#include "Enemigo.h"
#include "Inventory.h"

// Fábricas de plataformas
#include "FabricaPlataformas.h"
#include "FabricaAerea.h"
#include "FabricaTerrestre.h"
#include "FabricaAcuatica.h"
#include "FabricaSubterranea.h"

// Fábricas de enemigos
#include "FabricaEnemigos.h"
#include "FabricaEnemigosNaturales.h"
#include "FabricaEnemigosTecnologicos.h"

AAventuraUSFX022026L1GameMode::AAventuraUSFX022026L1GameMode()
{
	DefaultPawnClass = AAventuraUSFX022026L1Pawn::StaticClass();
	tipoPlataformaActual = 0;
	tipoEnemigoActual = 0;
}

void AAventuraUSFX022026L1GameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	// PLATAFORMAS (Factory Method)
	TArray<AFabricaPlataformas*> FabricasDisponibles;
	FabricasDisponibles.Add(World->SpawnActor<AFabricaAerea>(AFabricaAerea::StaticClass()));
	FabricasDisponibles.Add(World->SpawnActor<AFabricaTerrestre>(AFabricaTerrestre::StaticClass()));
	FabricasDisponibles.Add(World->SpawnActor<AFabricaAcuatica>(AFabricaAcuatica::StaticClass()));
	FabricasDisponibles.Add(World->SpawnActor<AFabricaSubterranea>(AFabricaSubterranea::StaticClass()));

	for (AFabricaPlataformas* FabricaActual : FabricasDisponibles)
	{
		if (FabricaActual == nullptr) continue;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,
			FString::Printf(TEXT("Fabrica Plataforma: %s"), *FabricaActual->GetClass()->GetName()));

		FRotator Rotacion = FRotator::ZeroRotator;

		for (int i = 0; i < 10; i++)
		{
			FVector SpawnLocation = FVector(
				FMath::RandRange(-1500.0f, 1500.0f),
				FMath::RandRange(-1500.0f, 1500.0f),
				FMath::RandRange(50.0f, 1000.0f));

			APlataforma* NuevaPlataforma = FabricaActual->CrearPlataforma(SpawnLocation, Rotacion);
			if (NuevaPlataforma)
			{
				aPlataformas.Add(NuevaPlataforma);
			}
		}
	}

	// ENEMIGOS (Abstract Factory)
	TArray<AFabricaEnemigos*> FabricasEnemigos;
	FabricasEnemigos.Add(World->SpawnActor<AFabricaEnemigosNaturales>(AFabricaEnemigosNaturales::StaticClass()));
	FabricasEnemigos.Add(World->SpawnActor<AFabricaEnemigosTecnologicos>(AFabricaEnemigosTecnologicos::StaticClass()));

	TArray<FIntVector> CantidadesPorFamilia;
	CantidadesPorFamilia.Add(FIntVector(5, 5, 5));  //  Naturales
	CantidadesPorFamilia.Add(FIntVector(3, 3, 3));  //  Tecnológicos

	// Bucle que recorre cada familia
	for (int f = 0; f < FabricasEnemigos.Num(); f++)
	{
		AFabricaEnemigos* FabricaActual = FabricasEnemigos[f];
		if (FabricaActual == nullptr) continue;
		if (f >= CantidadesPorFamilia.Num()) continue;

		FIntVector Cantidades = CantidadesPorFamilia[f];

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Cyan,
			FString::Printf(TEXT("%s -> Aereos:%d Acuaticos:%d Terrestres:%d"),
				*FabricaActual->GetClass()->GetName(),
				Cantidades.X, Cantidades.Y, Cantidades.Z));

		FRotator Rotacion = FRotator::ZeroRotator;

		// Aereos
		for (int i = 0; i < Cantidades.X; i++)
		{
			FVector Loc = FVector(
				FMath::RandRange(-1500.0f, 1500.0f),
				FMath::RandRange(-1500.0f, 1500.0f),
				FMath::RandRange(800.0f, 1400.0f));

			AEnemigo* N = FabricaActual->CrearEnemigoAereo(Loc, Rotacion);
			if (N) aEnemigos.Add(N);
		}

		// Acuaticos
		for (int i = 0; i < Cantidades.Y; i++)
		{
			FVector Loc = FVector(
				FMath::RandRange(-1000.0f, 1000.0f),
				FMath::RandRange(-1000.0f, 1000.0f),
				FMath::RandRange(300.0f, 700.0f));

			AEnemigo* N = FabricaActual->CrearEnemigoAcuatico(Loc, Rotacion);
			if (N) aEnemigos.Add(N);
		}

		// Terrestres
		for (int i = 0; i < Cantidades.Z; i++)
		{
			FVector Loc = FVector(
				FMath::RandRange(-1200.0f, 1200.0f),
				FMath::RandRange(-1200.0f, 1200.0f),
				FMath::RandRange(100.0f, 300.0f));

			AEnemigo* N = FabricaActual->CrearEnemigoTerrestre(Loc, Rotacion);
			if (N) aEnemigos.Add(N);
		}
	}

	// TIMERS
	GetWorldTimerManager().SetTimer(TimerEliminarPlataforma, this, &AAventuraUSFX022026L1GameMode::EliminarPlataforma, 1.0f, true);
	GetWorldTimerManager().SetTimer(TimerEliminarEnemigo, this, &AAventuraUSFX022026L1GameMode::EliminarEnemigo, 3.0f, true);
}

void AAventuraUSFX022026L1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAventuraUSFX022026L1GameMode::EliminarPlataforma()
{
	for (int32 i = 0; i < aPlataformas.Num(); i++)
	{
		if (aPlataformas[i] != nullptr && aPlataformas[i]->tipoPlataforma == static_cast<ETipoPlataforma>(tipoPlataformaActual))
		{
			aPlataformas[i]->Destroy();
			aPlataformas.RemoveAt(i);
			break;
		}
	}

	tipoPlataformaActual = (tipoPlataformaActual >= 3) ? 0 : tipoPlataformaActual + 1;
}

void AAventuraUSFX022026L1GameMode::EliminarEnemigo()
{
	for (int32 i = 0; i < aEnemigos.Num(); i++)
	{
		if (aEnemigos[i] != nullptr && aEnemigos[i]->tipoEnemigo == static_cast<ETipoEnemigo>(tipoEnemigoActual))
		{
			aEnemigos[i]->Destroy();
			aEnemigos.RemoveAt(i);
			break;
		}
	}

	tipoEnemigoActual = (tipoEnemigoActual >= 2) ? 0 : tipoEnemigoActual + 1;
}