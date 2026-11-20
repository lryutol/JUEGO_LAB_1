#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NaveNodriza.generated.h"

class UEstadoNaveNodriza;
class UStaticMeshComponent;

UCLASS()
class AVENTURAUSFX022026L1_API ANaveNodriza : public AActor
{
	GENERATED_BODY()
public:
	ANaveNodriza();

	// Componentes ensamblados
	UPROPERTY() UStaticMeshComponent* CompCasco;
	UPROPERTY() UStaticMeshComponent* CompMotores;
	UPROPERTY() UStaticMeshComponent* CompTorretas;

	float VidaActual = 3000.0f;
	float VidaMaxima = 3000.0f;
	class APawn* JugadorObjetivo;

	// Puntero al patrón State
	UPROPERTY()
	UEstadoNaveNodriza* EstadoActual;

	void CambiarEstado(UEstadoNaveNodriza* NuevoEstado);
	void EnsamblarPartes(UStaticMesh* Casco, FVector EscalaCasco, UStaticMesh* Motor, FVector EscalaMotor, UStaticMesh* Torreta, FVector EscalaTorreta);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};