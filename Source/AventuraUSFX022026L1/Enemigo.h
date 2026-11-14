#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemigo.generated.h"

class UStaticMeshComponent;
class AAventuraUSFX022026L1Projectile;

UENUM(BlueprintType)
enum class EPatronMovimiento : uint8
{
	Circulo,
	Cascada,
	Aleatorio,
	RutaLineal,
	Persecucion
};

enum class ETipoEnemigo
{
	ENEMIGO_TERRESTRE,
	ENEMIGO_ACUATICO,
	ENEMIGO_AEREO
};

struct FConfigEnemigo
{
	ETipoEnemigo Tipo = ETipoEnemigo::ENEMIGO_TERRESTRE;
	FString MallaRuta = TEXT("");
	FString RutaMaterial = TEXT("");
	FVector Escala = FVector(1.0f, 1.0f, 1.0f);
	float Vida = 100.0f;

	EPatronMovimiento Patron = EPatronMovimiento::RutaLineal;
	FVector CentroPatron = FVector(0.0f, 0.0f, 0.0f);
	float Velocidad = 300.0f;
	float RangoDeteccion = 1500.0f;
	float RangoAtaque = 1000.0f;

	int32 IndiceFormacion = 0;
	int32 TotalFormacion = 1;
};

UCLASS()
class AVENTURAUSFX022026L1_API AEnemigo : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemigo();

	ETipoEnemigo tipoEnemigo;
	UStaticMeshComponent* mallaEnemigo;

	void Configurar(const FConfigEnemigo& Config);
	virtual void RecibirDanio(float Cantidad);

	EPatronMovimiento PatronBase;
	FVector CentroPatron;
	float VelocidadMovimiento;
	float RangoDeteccion;
	float RangoAtaque;
	float TiempoPatron;

	int32 IndiceFormacion;
	int32 TotalFormacion;

	FVector PuntoRutaA;
	FVector PuntoRutaB;
	FVector DestinoActual;

	float vidaMaxima;
	float vidaActual;
	bool bEstaPersiguiendo;
	bool bEsCaotico; // Bandera para el caos
	class APawn* JugadorObjetivo;
	float TiempoDesdeUltimoDanio;

	UFUNCTION()
	void RecibirAlerta();

	UFUNCTION()
	void RecibirFinAlerta();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void DispararAlJugador();

public:
	virtual void Tick(float DeltaTime) override;

private:
	void MoverCirculo(float DeltaTime);
	void MoverCascada(float DeltaTime);
	void MoverAleatorio(float DeltaTime);
	void MoverRutaLineal(float DeltaTime);
	void MoverPersecucion(float DeltaTime);
	void MoverCaotico(float DeltaTime); // Función del caos
	FVector PuntoAleatorio;

	FTimerHandle TimerDisparo;
	float TiempoEntreDisparos = 2.0f;
};