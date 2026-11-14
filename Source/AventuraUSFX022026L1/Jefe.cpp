#include "Jefe.h"
#include "EstrategiaFactory.h"
#include "Torreta.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "AventuraUSFX022026L1Pawn.h" // Para leer la velocidad del Pawn

AJefe::AJefe()
{
	TorretasDestruidas = 0;
	bFaseMediaActivada = false;
	bFaseFinalActivada = false;
	bEstaHuyendo = false;

	tipoEnemigo = ETipoEnemigo::ENEMIGO_AEREO;
}

void AJefe::BeginPlay()
{
	Super::BeginPlay();

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}

	CambiarEstrategia(1);

	for (TActorIterator<ATorreta> It(GetWorld()); It; ++It)
	{
		if (*It) (*It)->OnTorretaDestruida.AddDynamic(this, &AJefe::AlDestruirTorreta);
	}

	GetWorldTimerManager().SetTimer(TimerAtaqueJefe, this, &AJefe::EjecutarAtaque, 2.0f, true);
}

void AJefe::CambiarEstrategia(int32 Fase)
{
	if (EstrategiaActual) EstrategiaActual->ConditionalBeginDestroy();
	EstrategiaActual = FEstrategiaFactory::CrearEstrategia(Fase);
}

void AJefe::AlDestruirTorreta()
{
	TorretasDestruidas++;
	UE_LOG(LogTemp, Warning, TEXT("Jefe: ¡Torreta destruida! Total: %d"), TorretasDestruidas);

	if (TorretasDestruidas == 1 && !bFaseMediaActivada && !bFaseFinalActivada) CambiarEstrategia(2);
	else if (TorretasDestruidas == 2 && !bFaseMediaActivada && !bFaseFinalActivada) CambiarEstrategia(3);
}

void AJefe::RecibirDanio(float Cantidad)
{
	Super::RecibirDanio(Cantidad);

	if (GEngine && vidaMaxima > 0.0f)
	{
		float Porcentaje = (vidaActual / vidaMaxima) * 100.0f;
		FString Mensaje = FString::Printf(TEXT("JEFE: %.1f%% de Vida"), Porcentaje);
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, Mensaje);
	}

	if (vidaActual <= (vidaMaxima * 0.5f) && !bFaseMediaActivada && !bFaseFinalActivada)
	{
		bFaseMediaActivada = true;
		CambiarEstrategia(4);
		UE_LOG(LogTemp, Warning, TEXT("Jefe: ¡Vida al 50%! Cambiando a abanico."));
	}

	if (vidaActual <= (vidaMaxima * 0.1f) && !bFaseFinalActivada)
	{
		bFaseFinalActivada = true;
		bEstaHuyendo = true;
		CambiarEstrategia(5);
		UE_LOG(LogTemp, Warning, TEXT("Jefe: ¡Vida al 10%! Huyendo y lanzando red."));
	}
}

void AJefe::EjecutarAtaque()
{
	if (EstrategiaActual && JugadorObjetivo)
	{
		EstrategiaActual->Atacar(this);
	}
}

void AJefe::Tick(float DeltaTime)
{
	if (!JugadorObjetivo) return;

	FVector TargetLoc = JugadorObjetivo->GetActorLocation();
	FVector DireccionHaciaJugador = (TargetLoc - GetActorLocation()).GetSafeNormal();

	if (!DireccionHaciaJugador.IsNearlyZero())
	{
		if (bEstaHuyendo)
		{
			// Huye en dirección opuesta libremente (sin restricción de Z)
			FVector DireccionHuida = -DireccionHaciaJugador;
			SetActorRotation(DireccionHuida.Rotation());

			// 20% más rápido que el Pawn
			float VelocidadHuida = 2400.0f;
			if (AAventuraUSFX022026L1Pawn* Pawn = Cast<AAventuraUSFX022026L1Pawn>(JugadorObjetivo))
			{
				VelocidadHuida = Pawn->MoveSpeed * 1.2f;
			}

			SetActorLocation(GetActorLocation() + (DireccionHuida * VelocidadHuida * DeltaTime), true);
		}
		else
		{
			SetActorRotation(DireccionHaciaJugador.Rotation());
			SetActorLocation(GetActorLocation() + (DireccionHaciaJugador * (VelocidadMovimiento * 1.0f) * DeltaTime), true);
		}
	}
}