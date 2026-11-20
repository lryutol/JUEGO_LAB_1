#include "EstadoNaveNodriza.h"
#include "NaveNodriza.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

void UEstadoNaveNormal::Tick(ANaveNodriza* Nave, float DeltaTime)
{
	// Movimiento lento
	if (Nave->JugadorObjetivo)
	{
		FVector Direccion = (Nave->JugadorObjetivo->GetActorLocation() - Nave->GetActorLocation()).GetSafeNormal();
		Nave->SetActorLocation(Nave->GetActorLocation() + (Direccion * 150.0f * DeltaTime));
	}
}

void UEstadoNaveAveriada::Entrar(ANaveNodriza* Nave)
{
	// Efecto visual: quemar motores
	if (Nave->CompMotores) Nave->CompMotores->SetVisibility(false);
}

void UEstadoNaveAveriada::Tick(ANaveNodriza* Nave, float DeltaTime)
{
	// Se mueve erráticamente
	if (Nave->JugadorObjetivo)
	{
		FVector Direccion = (Nave->JugadorObjetivo->GetActorLocation() - Nave->GetActorLocation()).GetSafeNormal();
		FVector Desvio = FVector(0, FMath::Sin(Nave->GetGameTimeSinceCreation() * 5.0f) * 500.0f, 0); // Zigzag
		Nave->SetActorLocation(Nave->GetActorLocation() + ((Direccion + Desvio) * 300.0f * DeltaTime));
	}
}

void UEstadoNaveCritica::Entrar(ANaveNodriza* Nave)
{
	// Efecto visual: el casco parpadea
	if (Nave->CompCasco) Nave->CompCasco->SetVisibility(false);
}

void UEstadoNaveCritica::Tick(ANaveNodriza* Nave, float DeltaTime)
{
	// Huye a toda velocidad
	if (Nave->JugadorObjetivo)
	{
		FVector Direccion = (Nave->JugadorObjetivo->GetActorLocation() - Nave->GetActorLocation()).GetSafeNormal();
		FVector Huida = -Direccion;
		Nave->SetActorLocation(Nave->GetActorLocation() + (Huida * 800.0f * DeltaTime));
	}
}