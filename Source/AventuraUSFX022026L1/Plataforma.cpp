// Fill out your copyright notice in the Description page of Project Settings.

#include "Plataforma.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

APlataforma::APlataforma()
{
	PrimaryActorTick.bCanEverTick = true;

	tipoPlataforma = ETipoPlataforma::PLATAFORMA_TERRESTRE;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlataformaMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane'"));

	mallaPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaPlataforma"));
	mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
	mallaPlataforma->SetupAttachment(RootComponent);

	RootComponent = mallaPlataforma;

	movimientoEjes = FVector(0.0f, 0.0f, 0.0f);
	movimientoLimitesMaximos = FVector(800.0f, 800.0f, 800.0f);
	movimientoLimitesMinimos = FVector(-800.0f, -800.0f, -800.0f);
	movimientoVelocidades = FVector(0.0f, 0.0f, 0.0f);
	movimientoDireccion = FVector(1.0f, 1.0f, 1.0f);
}

void APlataforma::BeginPlay()
{
	Super::BeginPlay();
}

void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	posicionActual = GetActorLocation();

	// Si toca los límites, invierte la dirección de ese eje
	if (posicionActual.X >= movimientoLimitesMaximos.X || posicionActual.X <= movimientoLimitesMinimos.X) {
		movimientoDireccion.X *= -1.0f;
	}

	if (posicionActual.Y >= movimientoLimitesMaximos.Y || posicionActual.Y <= movimientoLimitesMinimos.Y) {
		movimientoDireccion.Y *= -1.0f;
	}

	if (posicionActual.Z >= movimientoLimitesMaximos.Z || posicionActual.Z <= movimientoLimitesMinimos.Z) {
		movimientoDireccion.Z *= -1.0f;
	}

	// Aplicamos el movimiento respetando los ejes habilitados de cada tipo
	FVector desplazamiento = movimientoDireccion * movimientoVelocidades * movimientoEjes * DeltaTime;
	FVector posicionNueva = posicionActual + desplazamiento;
	SetActorLocation(posicionNueva);
}