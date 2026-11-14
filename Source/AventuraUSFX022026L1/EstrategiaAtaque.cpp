#include "EstrategiaAtaque.h"
#include "Jefe.h"
#include "AventuraUSFX022026L1Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "FabricaEnemigosTecnologicos.h"

void UEAtaqueBasico::Atacar(AJefe* Jefe)
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(Jefe->GetWorld(), 0);
	if (!Jugador) return;

	FVector SpawnLoc = Jefe->GetActorLocation() + Jefe->GetActorForwardVector() * 800.0f;
	FRotator SpawnRot = (Jugador->GetActorLocation() - SpawnLoc).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = Jefe;
	AAventuraUSFX022026L1Projectile* P = Jefe->GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(SpawnLoc, SpawnRot, Params);
	if (P) P->IgnorarActor(Jefe); // Ignora al jefe
}

void UEAtaquePesado::Atacar(AJefe* Jefe)
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(Jefe->GetWorld(), 0);
	if (!Jugador) return;

	FVector SpawnLoc = Jefe->GetActorLocation() + Jefe->GetActorForwardVector() * 800.0f;
	FRotator SpawnRot = (Jugador->GetActorLocation() - SpawnLoc).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = Jefe;
	AAventuraUSFX022026L1Projectile* Proyectil = Jefe->GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(SpawnLoc, SpawnRot, Params);

	if (Proyectil)
	{
		Proyectil->IgnorarActor(Jefe); // Ignora al jefe
		Proyectil->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
		Proyectil->DanioProyectil = 40.0f;
	}
}

void UEAtaqueInvocar::Atacar(AJefe* Jefe)
{
	AFabricaEnemigosTecnologicos* Fabrica = Jefe->GetWorld()->SpawnActor<AFabricaEnemigosTecnologicos>();
	if (Fabrica)
	{
		for (int i = 0; i < 2; i++)
		{
			FVector Pos = Jefe->GetActorLocation() + FVector(FMath::RandRange(-300, 300), FMath::RandRange(-300, 300), 200);
			Fabrica->CrearEnemigoAereo(Pos, FRotator::ZeroRotator, i, 2);
		}
	}
}

void UEAtaqueAbanico::Atacar(AJefe* Jefe)
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(Jefe->GetWorld(), 0);
	if (!Jugador) return;

	FVector SpawnLocBase = Jefe->GetActorLocation() + Jefe->GetActorForwardVector() * 800.0f;
	FRotator SpawnRot = (Jugador->GetActorLocation() - SpawnLocBase).Rotation();

	FVector VectorDerecha = Jefe->GetActorRightVector();
	float Separacion = 200.0f;

	for (int i = -2; i <= 2; i++)
	{
		FVector PosicionFila = SpawnLocBase + (VectorDerecha * i * Separacion);
		FActorSpawnParameters Params; Params.Owner = Jefe;
		AAventuraUSFX022026L1Projectile* Proyectil = Jefe->GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(PosicionFila, SpawnRot, Params);

		if (Proyectil)
		{
			Proyectil->IgnorarActor(Jefe); // Ignora al jefe
			Proyectil->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
			Proyectil->DanioProyectil = 40.0f;
			Proyectil->SetVelocidad(5000.f);
		}
	}
}

void UEAtaqueRed::Atacar(AJefe* Jefe)
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(Jefe->GetWorld(), 0);
	if (!Jugador) return;

	FVector SpawnLocBase = Jefe->GetActorLocation() + Jefe->GetActorForwardVector() * 800.0f;
	FRotator SpawnRot = (Jugador->GetActorLocation() - SpawnLocBase).Rotation();

	FVector VectorDerecha = Jefe->GetActorRightVector();
	FVector VectorArriba = Jefe->GetActorUpVector();
	float Separacion = 200.0f;

	for (int i = -2; i <= 2; i++)
	{
		FVector Posicion = SpawnLocBase + (VectorDerecha * i * Separacion);
		FActorSpawnParameters Params; Params.Owner = Jefe;
		AAventuraUSFX022026L1Projectile* Proyectil = Jefe->GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(Posicion, SpawnRot, Params);
		if (Proyectil)
		{
			Proyectil->IgnorarActor(Jefe); // Ignora al jefe
			Proyectil->SetActorScale3D(FVector(2.5f));
			Proyectil->DanioProyectil = 40.0f;
			Proyectil->SetVelocidad(5000.f);
		}
	}

	for (int j = -2; j <= 2; j++)
	{
		FVector Posicion = SpawnLocBase + (VectorArriba * j * Separacion);
		FActorSpawnParameters Params; Params.Owner = Jefe;
		AAventuraUSFX022026L1Projectile* Proyectil = Jefe->GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(Posicion, SpawnRot, Params);
		if (Proyectil)
		{
			Proyectil->IgnorarActor(Jefe); // Ignora al jefe
			Proyectil->SetActorScale3D(FVector(2.5f));
			Proyectil->DanioProyectil = 40.0f;
			Proyectil->SetVelocidad(5000.f);
		}
	}
}