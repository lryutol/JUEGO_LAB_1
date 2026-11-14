#include "Torreta.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "AventuraUSFX022026L1Projectile.h"
#include "Engine/StaticMesh.h"

ATorreta::ATorreta()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TorretaMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	MallaTorreta = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaTorreta"));
	RootComponent = MallaTorreta;
	if (TorretaMesh.Succeeded()) MallaTorreta->SetStaticMesh(TorretaMesh.Object);
	MallaTorreta->SetWorldScale3D(FVector(2.0f, 2.0f, 3.0f));

	MallaTorreta->SetCollisionObjectType(ECC_WorldStatic);
	MallaTorreta->SetCollisionResponseToAllChannels(ECR_Block);

	bJugadorDetectado = false;
	bEstaMuerta = false; // Inicializamos
}

void ATorreta::BeginPlay()
{
	Super::BeginPlay();
	VidaActual = VidaMaxima;
}

void ATorreta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (VidaActual <= 0.0f || bEstaMuerta) return;

	if (!JugadorObjetivo)
	{
		JugadorObjetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (!JugadorObjetivo) return;
	}

	float Distancia = FVector::Dist(GetActorLocation(), JugadorObjetivo->GetActorLocation());

	if (Distancia <= RangoDeteccion)
	{
		if (!bJugadorDetectado)
		{
			bJugadorDetectado = true;
			OnAlertaTorreta.Broadcast();
			GetWorldTimerManager().SetTimer(TimerDisparo, this, &ATorreta::DispararAlJugador, TiempoEntreDisparos, true, 0.0f);
		}
	}
	else
	{
		if (bJugadorDetectado)
		{
			bJugadorDetectado = false;
			OnPeligroFinalizado.Broadcast();
			GetWorldTimerManager().ClearTimer(TimerDisparo);
		}
	}
}

void ATorreta::DispararAlJugador()
{
	if (!JugadorObjetivo || bEstaMuerta) return;

	FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 150.0f);
	FRotator SpawnRotation = (JugadorObjetivo->GetActorLocation() - SpawnLocation).Rotation();

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();

	GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(SpawnLocation, SpawnRotation, Params);
}

float ATorreta::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bEstaMuerta) return 0.0f;

	VidaActual -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Torreta recibió daño. Vida restante: %f"), VidaActual);

	if (VidaActual <= 0.0f)
	{
		Destroy();
	}
	return DamageAmount;
}

void ATorreta::Destroyed()
{
	// MARCADA COMO MUERTA ANTES DE AVISAR
	bEstaMuerta = true;

	OnTorretaDestruida.Broadcast();
	OnPeligroFinalizado.Broadcast();
	Super::Destroyed();
}