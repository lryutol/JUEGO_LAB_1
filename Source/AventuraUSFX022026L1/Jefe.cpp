#include "Jefe.h"
#include "EstrategiaFactory.h"
#include "Torreta.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/Engine.h"
#include "AventuraUSFX022026L1Pawn.h"

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
	}

	if (vidaActual <= (vidaMaxima * 0.1f) && !bFaseFinalActivada)
	{
		bFaseFinalActivada = true;
		bEstaHuyendo = true;
		CambiarEstrategia(5);
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
			// 1. Dirección base de huida (opuesta al jugador)
			FVector DireccionDeseada = -DireccionHaciaJugador;
			FVector AjusteEvasion = FVector::ZeroVector;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			FHitResult Hit;

			// =========================================================
			// 2. SENSOR DE OBSTÁCULOS FRONTALES (Paredes y Montañas)
			// =========================================================
			FVector FinFrente = GetActorLocation() + (DireccionDeseada * 2000.0f); // Rayo hacia adelante
			if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), FinFrente, ECC_WorldStatic, Params))
			{
				// Si hay una pared cerca, nos desviamos usando la normal de impacto
				// y sumamos un poco hacia arriba para buscar una curva natural
				AjusteEvasion += Hit.ImpactNormal * 3.0f;
				AjusteEvasion.Z += 1.5f;
			}

			// =========================================================
			// 3. SENSOR DEL SUELO (Evita que se estrelle)
			// =========================================================
			FVector FinSuelo = GetActorLocation() - FVector(0, 0, 2000.0f);
			if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), FinSuelo, ECC_WorldStatic, Params))
			{
				if (Hit.Distance < 1500.0f) // Si está a menos de 15m del suelo
				{
					float FuerzaEvasion = (1500.0f - Hit.Distance) / 1500.0f;
					AjusteEvasion.Z += FuerzaEvasion * 4.0f; // Fuerza de subida suave
				}
			}

			// =========================================================
			// 4. LÍMITES INVISIBLES (Evita que desaparezca)
			// =========================================================
			FVector Pos = GetActorLocation();

			// Si baja de Z=300, lo empujamos hacia arriba (fuerza invisible)
			if (Pos.Z < 300.0f) AjusteEvasion.Z += 3.0f;

			// Si sale de los límites X o Y del mapa (ej. +/- 5000), lo empujamos al centro
			if (Pos.X < -5000.0f) AjusteEvasion.X += 4.0f;
			if (Pos.X > 5000.0f)  AjusteEvasion.X -= 4.0f;
			if (Pos.Y < -5000.0f) AjusteEvasion.Y += 4.0f;
			if (Pos.Y > 5000.0f)  AjusteEvasion.Y -= 4.0f;

			// =========================================================
			// 5. APLICAMOS LA CURVA NATURAL
			// =========================================================
			FVector DireccionFinal = (DireccionDeseada + AjusteEvasion).GetSafeNormal();
			FRotator RotacionObjetivo = DireccionFinal.Rotation();

			// Interpolación suave para que el giro sea una curva (RInterpTo)
			FRotator NuevaRotacion = FMath::RInterpTo(GetActorRotation(), RotacionObjetivo, DeltaTime, 3.0f);
			SetActorRotation(NuevaRotacion);

			// 6. Velocidad: Solo 2% más rápida que el Pawn
			float VelocidadHuida = 1700.0f;
			if (AAventuraUSFX022026L1Pawn* Pawn = Cast<AAventuraUSFX022026L1Pawn>(JugadorObjetivo))
			{
				VelocidadHuida = Pawn->MoveSpeed * 1.02f;
			}

			// Movemos al Jefe usando su nueva rotación curva
			SetActorLocation(GetActorLocation() + (NuevaRotacion.Vector() * VelocidadHuida * DeltaTime), true);
		}
		else
		{
			// Persecución normal (sigue igual)
			FRotator RotacionObjetivo = DireccionHaciaJugador.Rotation();
			FRotator NuevaRotacion = FMath::RInterpTo(GetActorRotation(), RotacionObjetivo, DeltaTime, 5.0f);
			SetActorRotation(NuevaRotacion);
			SetActorLocation(GetActorLocation() + (NuevaRotacion.Vector() * (VelocidadMovimiento * 1.0f) * DeltaTime), true);
		}
	}
}