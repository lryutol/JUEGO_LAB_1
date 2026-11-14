#include "AventuraUSFX022026L1GameMode.h"
#include "AventuraUSFX022026L1Pawn.h"
#include "FachadaJuego.h"

AAventuraUSFX022026L1GameMode::AAventuraUSFX022026L1GameMode()
{
	DefaultPawnClass = AAventuraUSFX022026L1Pawn::StaticClass();
}

void AAventuraUSFX022026L1GameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	MiFachada = World->SpawnActor<AFachadaJuego>(AFachadaJuego::StaticClass());

	if (MiFachada)
	{
		// 1. Drones por esquina
		// 2. Drones por esquina
		// 3. Acuáticos totales
		// 4. Grupos de Tanques (3x3 = 9 c/u)
		// 5. Grupos de Lobos (3x3 = 9 c/u)
		// =========================================================
		MiFachada->InicializarMundo(20, 20, 50, 5, 4);
	}

	GetWorldTimerManager().SetTimer(TimerEliminarPlataforma, this, &AAventuraUSFX022026L1GameMode::EliminarPlataforma, 10.0f, true);
	GetWorldTimerManager().SetTimer(TimerEliminarEnemigo, this, &AAventuraUSFX022026L1GameMode::EliminarEnemigo, 5.0f, true);
}

void AAventuraUSFX022026L1GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAventuraUSFX022026L1GameMode::EliminarPlataforma()
{
	if (MiFachada)
	{
		MiFachada->EliminarSiguientePlataforma();
	}
}

void AAventuraUSFX022026L1GameMode::EliminarEnemigo()
{
	if (MiFachada)
	{
		MiFachada->EliminarSiguienteEnemigo();
	}
}