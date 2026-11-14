#include "Enemigo.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "AventuraUSFX022026L1Projectile.h"
#include "EngineUtils.h" 
#include "AIController.h" 
#include "Torreta.h"

AEnemigo::AEnemigo()
{
	PrimaryActorTick.bCanEverTick = true;
	tipoEnemigo = ETipoEnemigo::ENEMIGO_TERRESTRE;
	bEstaPersiguiendo = false;
	bEsCaotico = false;
	TiempoDesdeUltimoDanio = 0.0f;

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	if (GetMesh()) GetMesh()->SetVisibility(false);

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	}

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCapsuleSize(50.0f, 50.0f);
		GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemigo::OnCapsuleOverlap);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	mallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	if (DefaultMesh.Succeeded()) mallaEnemigo->SetStaticMesh(DefaultMesh.Object);
	mallaEnemigo->SetupAttachment(GetCapsuleComponent());

	mallaEnemigo->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	vidaMaxima = 100.0f;
	vidaActual = 100.0f;
}

void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	vidaActual = vidaMaxima;
	JugadorObjetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	for (TActorIterator<ATorreta> It(GetWorld()); It; ++It)
	{
		ATorreta* TorretaActual = *It;
		if (TorretaActual)
		{
			TorretaActual->OnAlertaTorreta.AddDynamic(this, &AEnemigo::RecibirAlerta);
			TorretaActual->OnPeligroFinalizado.AddDynamic(this, &AEnemigo::RecibirFinAlerta);
		}
	}
}

void AEnemigo::Configurar(const FConfigEnemigo& Config)
{
	tipoEnemigo = Config.Tipo;
	PatronBase = Config.Patron;
	CentroPatron = Config.CentroPatron;
	VelocidadMovimiento = Config.Velocidad;
	RangoDeteccion = Config.RangoDeteccion;
	RangoAtaque = Config.RangoAtaque;
	IndiceFormacion = Config.IndiceFormacion;
	TotalFormacion = Config.TotalFormacion;

	UStaticMesh* Malla = LoadObject<UStaticMesh>(nullptr, *Config.MallaRuta);
	if (Malla && mallaEnemigo)
	{
		mallaEnemigo->SetStaticMesh(Malla);
		mallaEnemigo->SetWorldScale3D(Config.Escala);
	}

	if (!Config.RutaMaterial.IsEmpty() && mallaEnemigo)
	{
		UMaterialInterface* MaterialCargado = LoadObject<UMaterialInterface>(nullptr, *Config.RutaMaterial);
		if (MaterialCargado) mallaEnemigo->SetMaterial(0, MaterialCargado);
	}

	vidaMaxima = Config.Vida;
	vidaActual = Config.Vida;
	TiempoPatron = 0.0f;
	PuntoAleatorio = GetActorLocation();

	if (tipoEnemigo == ETipoEnemigo::ENEMIGO_TERRESTRE || tipoEnemigo == ETipoEnemigo::ENEMIGO_ACUATICO)
	{
		GetCharacterMovement()->GravityScale = 1.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GetCharacterMovement()->MaxWalkSpeed = Config.Velocidad;

		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

		PuntoRutaA = Config.CentroPatron;
		PuntoRutaB = FVector(Config.CentroPatron.X, -4000.0f, Config.CentroPatron.Z);
		DestinoActual = PuntoRutaB;
	}
	else
	{
		GetCharacterMovement()->GravityScale = 0.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}
}

void AEnemigo::RecibirFinAlerta()
{
	bEstaPersiguiendo = false;

	int32 TorretasRestantes = 0;
	for (TActorIterator<ATorreta> It(GetWorld()); It; ++It)
	{
		// CORRECCIÓN: Contamos solo las torretas que NO estén muertas
		if (IsValid(*It) && !It->bEstaMuerta)
		{
			TorretasRestantes++;
		}
	}

	if (TorretasRestantes == 0)
	{
		PatronBase = EPatronMovimiento::Aleatorio;
		bEsCaotico = true;
		GetCharacterMovement()->MaxWalkSpeed = VelocidadMovimiento * 2.5f;
		UE_LOG(LogTemp, Warning, TEXT("¡Todas las torretas destruidas! Enemigo en modo caótico."));
	}
}

void AEnemigo::RecibirAlerta()
{
	bEstaPersiguiendo = true;
}

void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TiempoDesdeUltimoDanio > 0.0f) TiempoDesdeUltimoDanio -= DeltaTime;
	if (!JugadorObjetivo) return;

	if (bEstaPersiguiendo && !bEsCaotico)
	{
		float DistanciaAlJugador = FVector::Dist(GetActorLocation(), JugadorObjetivo->GetActorLocation());

		if (tipoEnemigo == ETipoEnemigo::ENEMIGO_TERRESTRE || tipoEnemigo == ETipoEnemigo::ENEMIGO_ACUATICO)
		{
			if (DistanciaAlJugador > RangoAtaque)
			{
				MoverPersecucion(DeltaTime);
			}
			else
			{
				FVector Direccion = (JugadorObjetivo->GetActorLocation() - GetActorLocation()).GetSafeNormal();
				SetActorRotation(Direccion.Rotation());
				if (!GetWorldTimerManager().IsTimerActive(TimerDisparo))
				{
					GetWorldTimerManager().SetTimer(TimerDisparo, this, &AEnemigo::DispararAlJugador, TiempoEntreDisparos, true, 0.0f);
				}
			}
		}
		else
		{
			MoverPersecucion(DeltaTime);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerDisparo);

		if (bEsCaotico)
		{
			MoverCaotico(DeltaTime);
		}
		else
		{
			switch (PatronBase)
			{
			case EPatronMovimiento::Circulo: MoverCirculo(DeltaTime); break;
			case EPatronMovimiento::Cascada: MoverCascada(DeltaTime); break;
			case EPatronMovimiento::Aleatorio: MoverAleatorio(DeltaTime); break;
			case EPatronMovimiento::RutaLineal: MoverRutaLineal(DeltaTime); break;
			default: break;
			}
		}
	}
}

void AEnemigo::MoverCaotico(float DeltaTime)
{
	if (FVector::Dist(GetActorLocation(), PuntoAleatorio) < 300.0f || FMath::RandRange(0, 20) < 1)
	{
		PuntoAleatorio = GetActorLocation() + FVector(FMath::RandRange(-4000.0f, 4000.0f), FMath::RandRange(-4000.0f, 4000.0f), 0.0f);
	}

	FVector Direccion = (PuntoAleatorio - GetActorLocation()).GetSafeNormal();

	if (tipoEnemigo == ETipoEnemigo::ENEMIGO_TERRESTRE || tipoEnemigo == ETipoEnemigo::ENEMIGO_ACUATICO)
	{
		AddMovementInput(Direccion, 1.0f);
	}
	else
	{
		SetActorLocation(GetActorLocation() + (Direccion * (VelocidadMovimiento * 2.5f) * DeltaTime));
	}

	AddActorLocalRotation(FRotator(0.0f, FMath::RandRange(-15.0f, 15.0f), 0.0f));
}

void AEnemigo::MoverRutaLineal(float DeltaTime)
{
	TiempoPatron += DeltaTime;
	float TiempoViaje = 25.0f;
	float CicloCompleto = TiempoViaje * 2.0f;
	float TiempoEnCiclo = FMath::Fmod(TiempoPatron, CicloCompleto);
	bool bIrHaciaB = TiempoEnCiclo < TiempoViaje;

	FVector Target = bIrHaciaB ? PuntoRutaB : PuntoRutaA;
	FVector Target2D = FVector(GetActorLocation().X, Target.Y, GetActorLocation().Z);
	FVector Direccion = (Target2D - GetActorLocation()).GetSafeNormal();

	if (!Direccion.IsNearlyZero() && FMath::Abs(Target.Y - GetActorLocation().Y) > 50.0f)
	{
		AddMovementInput(Direccion, 1.0f);
	}
}

void AEnemigo::MoverCirculo(float DeltaTime)
{
	TiempoPatron += DeltaTime * (VelocidadMovimiento / 800.0f);
	float OffsetAngulo = (360.0f / (TotalFormacion > 0 ? TotalFormacion : 1)) * IndiceFormacion;
	float AnguloFinal = TiempoPatron + FMath::DegreesToRadians(OffsetAngulo);

	float X = CentroPatron.X + FMath::Cos(AnguloFinal) * 800.0f;
	float Y = CentroPatron.Y + FMath::Sin(AnguloFinal) * 800.0f;
	SetActorLocation(FVector(X, Y, GetActorLocation().Z));

	FVector Tangente = FVector(-FMath::Sin(AnguloFinal), FMath::Cos(AnguloFinal), 0.0f);
	SetActorRotation(Tangente.Rotation());
}

void AEnemigo::MoverCascada(float DeltaTime)
{
	TiempoPatron += DeltaTime * 2.0f;
	float ZOffset = FMath::Sin(TiempoPatron) * 100.0f;
	FVector NuevaPos = GetActorLocation();
	NuevaPos.Z = CentroPatron.Z + ZOffset;
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), NuevaPos, DeltaTime, 5.0f));
}

void AEnemigo::MoverAleatorio(float DeltaTime)
{
	if (FVector::Dist(GetActorLocation(), PuntoAleatorio) < 150.0f)
	{
		UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (NavSys)
		{
			FNavLocation Result;
			if (NavSys->GetRandomReachablePointInRadius(GetActorLocation(), 2000.0f, Result))
			{
				PuntoAleatorio = Result.Location;
			}
		}
	}
	FVector Direccion = (PuntoAleatorio - GetActorLocation()).GetSafeNormal();
	AddMovementInput(Direccion, 1.0f);
	if (!Direccion.IsNearlyZero()) SetActorRotation(Direccion.Rotation());
}

void AEnemigo::MoverPersecucion(float DeltaTime)
{
	FVector TargetLoc = JugadorObjetivo->GetActorLocation();

	if (tipoEnemigo == ETipoEnemigo::ENEMIGO_TERRESTRE || tipoEnemigo == ETipoEnemigo::ENEMIGO_ACUATICO)
	{
		TargetLoc.Z = GetActorLocation().Z;
	}

	FVector Direccion = (TargetLoc - GetActorLocation()).GetSafeNormal();

	if (tipoEnemigo == ETipoEnemigo::ENEMIGO_TERRESTRE || tipoEnemigo == ETipoEnemigo::ENEMIGO_ACUATICO)
	{
		AddMovementInput(Direccion, 1.0f);
	}
	else
	{
		SetActorLocation(GetActorLocation() + (Direccion * (VelocidadMovimiento * 1.5f) * DeltaTime));
	}
}

void AEnemigo::RecibirDanio(float Cantidad)
{
	vidaActual -= Cantidad;
	if (vidaActual <= 0.0f) Destroy();
}

void AEnemigo::DispararAlJugador()
{
	if (!JugadorObjetivo) return;
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = (JugadorObjetivo->GetActorLocation() - SpawnLocation).Rotation();
	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.Instigator = GetInstigator();
	GetWorld()->SpawnActor<AAventuraUSFX022026L1Projectile>(SpawnLocation, SpawnRotation, Params);
}

void AEnemigo::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor == JugadorObjetivo && TiempoDesdeUltimoDanio <= 0.0f)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 15.0f, GetInstigatorController(), this, UDamageType::StaticClass());
		TiempoDesdeUltimoDanio = 1.0f;
	}
}