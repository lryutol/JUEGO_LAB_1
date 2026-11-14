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
	if (PlataformaMeshAsset.Succeeded())
	{
		mallaPlataforma->SetStaticMesh(PlataformaMeshAsset.Object);
	}
	mallaPlataforma->SetupAttachment(RootComponent);
	RootComponent = mallaPlataforma;

	// Valores por defecto
	VelocidadAscensor = 1.0f;
	AmplitudAscensor = 200.0f;
	bEsHorizontal = false;
}

void APlataforma::BeginPlay()
{
	Super::BeginPlay();
	UbicacionInicial = GetActorLocation();
	// Desfase aleatorio para que no se muevan todas al mismo tiempo
	TiempoPlataforma = FMath::RandRange(0.0f, 10.0f);
}

void APlataforma::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TiempoPlataforma += DeltaTime * VelocidadAscensor;

	// El movimiento Senoidal da ese efecto suave de "ascensor" o vaivén
	float Offset = FMath::Sin(TiempoPlataforma) * AmplitudAscensor;

	FVector NuevaPos = UbicacionInicial;
	if (bEsHorizontal)
	{
		NuevaPos.Y += Offset; // Movimiento en el eje Y (o cambia a X)
	}
	else
	{
		NuevaPos.Z += Offset; // Movimiento vertical
	}

	SetActorLocation(NuevaPos);
}