#include "FachadaJuego.h"
#include "Plataforma.h"
#include "Enemigo.h"
#include "FabricaEnemigosNaturales.h"
#include "FabricaEnemigosTecnologicos.h"
#include "FabricaAerea.h"
#include "FabricaTerrestre.h"
#include "FabricaAcuatica.h"
#include "FabricaSubterranea.h"
#include "Torreta.h"
#include "DirectorNaveNodriza.h"
#include "NaveNodrizaBuilder.h"
#include "NaveNodriza.h"
#include "Engine/StaticMesh.h" 

AFachadaJuego::AFachadaJuego()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFachadaJuego::BeginPlay()
{
	Super::BeginPlay();
}

void AFachadaJuego::InicializarMundo(int32 DronesTechPorEsquina, int32 DronesNatPorEsquina, int32 CantidadAcuaticos, int32 NumGruposTanques, int32 NumGruposLobos)
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("FACHADA ACTIVA: DronesTech: %d, Tanques: %d grupos"), DronesTechPorEsquina, NumGruposTanques));
	}

	// --- 0. TORRETAS ---
	World->SpawnActor<ATorreta>(ATorreta::StaticClass(), FVector(1500.0f, 1500.0f, 250.0f), FRotator::ZeroRotator);
	World->SpawnActor<ATorreta>(ATorreta::StaticClass(), FVector(-1500.0f, -1500.0f, 250.0f), FRotator::ZeroRotator);

	// --- 1. CREACIÓN DEL JEFE FINAL (NAVE NODRIZA) ---
	// Usamos la clase F directamente (sin NewObject)
	FNaveNodrizaBuilder BuilderNave;
	ANaveNodriza* NaveJefe = FDirectorNaveNodriza::ConstruirNaveDeAsalto(BuilderNave, GetWorld(), FVector(0.0f, 0.0f, 1500.0f), FRotator::ZeroRotator);

	if (NaveJefe)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fachada: Nave Nodriza ensamblada con éxito."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fachada: Falló la creación de la Nave Nodriza."));
	}

	// --- 2. PLATAFORMAS ---
	TArray<AFabricaPlataformas*> FabricasPlat;
	FabricasPlat.Add(World->SpawnActor<AFabricaTerrestre>());
	FabricasPlat.Add(World->SpawnActor<AFabricaAerea>());
	FabricasPlat.Add(World->SpawnActor<AFabricaAcuatica>());
	FabricasPlat.Add(World->SpawnActor<AFabricaSubterranea>());

	for (AFabricaPlataformas* Fabrica : FabricasPlat)
	{
		if (!Fabrica) continue;
		for (int i = 0; i < 15; i++)
		{
			float X = FMath::RandRange(-4000.0f, 4000.0f);
			float Y = FMath::RandRange(-4000.0f, 4000.0f);
			float Z = FMath::RandRange(200.0f, 800.0f);
			APlataforma* P = Fabrica->CrearPlataforma(FVector(X, Y, Z), FRotator::ZeroRotator);
			if (P) aPlataformas.Add(P);
		}
	}

	// --- 3. FÁBRICAS DE ENEMIGOS NORMALES ---
	AFabricaEnemigos* FabricaTech = World->SpawnActor<AFabricaEnemigosTecnologicos>();
	AFabricaEnemigos* FabricaNat = World->SpawnActor<AFabricaEnemigosNaturales>();

	// --- 4. DRONES TECNOLÓGICOS ---
	if (FabricaTech && DronesTechPorEsquina > 0)
	{
		for (int i = 0; i < DronesTechPorEsquina; i++)
		{
			FabricaTech->CrearEnemigoAereo(FVector(-4000.0f, 4000.0f, 1500.0f), FRotator::ZeroRotator, i, DronesTechPorEsquina);
			FabricaTech->CrearEnemigoAereo(FVector(4000.0f, 4000.0f, 1500.0f), FRotator::ZeroRotator, i, DronesTechPorEsquina);
		}
	}

	// --- 5. DRONES Y ACUÁTICOS NATURALES ---
	if (FabricaNat)
	{
		if (DronesNatPorEsquina > 0)
		{
			for (int i = 0; i < DronesNatPorEsquina; i++)
			{
				FabricaNat->CrearEnemigoAereo(FVector(-4000.0f, -4000.0f, 1500.0f), FRotator::ZeroRotator, i, DronesNatPorEsquina);
				FabricaNat->CrearEnemigoAereo(FVector(4000.0f, -4000.0f, 1500.0f), FRotator::ZeroRotator, i, DronesNatPorEsquina);
			}
		}

		if (CantidadAcuaticos > 0)
		{
			for (int i = 0; i < CantidadAcuaticos; i++)
			{
				FVector Pos = FVector(FMath::RandRange(-3000.0f, 3000.0f), FMath::RandRange(-4500.0f, -2500.0f), -200.0f);
				FabricaNat->CrearEnemigoAcuatico(Pos, FRotator::ZeroRotator);
			}
		}
	}

	// --- 6. TANQUES TECNOLÓGICOS ---
	if (FabricaTech && NumGruposTanques > 0)
	{
		TArray<FVector> PosicionesBaseTanques;
		PosicionesBaseTanques.Add(FVector(-4000.0f, 3000.0f, 250.0f));
		PosicionesBaseTanques.Add(FVector(0.0f, 3000.0f, 250.0f));
		PosicionesBaseTanques.Add(FVector(4000.0f, 3000.0f, 250.0f));
		PosicionesBaseTanques.Add(FVector(-2000.0f, 1000.0f, 250.0f));
		PosicionesBaseTanques.Add(FVector(2000.0f, 1000.0f, 250.0f));

		for (int grupo = 0; grupo < NumGruposTanques; grupo++)
		{
			FVector Base = PosicionesBaseTanques[grupo % PosicionesBaseTanques.Num()];
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					FVector Pos = Base + FVector(x * 300.0f, y * 300.0f, 0);
					FabricaTech->CrearEnemigoTerrestre(Pos, FRotator::ZeroRotator);
				}
			}
		}
	}

	// --- 7. LOBOS NATURALES ---
	if (FabricaNat && NumGruposLobos > 0)
	{
		TArray<FVector> PosicionesBaseLobos;
		PosicionesBaseLobos.Add(FVector(-3000.0f, 1000.0f, 250.0f));
		PosicionesBaseLobos.Add(FVector(3000.0f, 1000.0f, 250.0f));
		PosicionesBaseLobos.Add(FVector(-1000.0f, 0.0f, 250.0f));
		PosicionesBaseLobos.Add(FVector(1000.0f, 0.0f, 250.0f));

		for (int grupo = 0; grupo < NumGruposLobos; grupo++)
		{
			FVector Base = PosicionesBaseLobos[grupo % PosicionesBaseLobos.Num()];
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					FVector Pos = Base + FVector(x * 300.0f, y * 300.0f, 0);
					FabricaNat->CrearEnemigoTerrestre(Pos, FRotator::ZeroRotator);
				}
			}
		}
	}
}

void AFachadaJuego::EliminarSiguientePlataforma()
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

void AFachadaJuego::EliminarSiguienteEnemigo()
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