#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AventuraUSFX022026L1Projectile.generated.h"

UCLASS()
class AVENTURAUSFX022026L1_API AAventuraUSFX022026L1Projectile : public AActor
{
	GENERATED_BODY()

public:
	AAventuraUSFX022026L1Projectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combate")
	float DanioProyectil = 20.0f;

	void SetVelocidad(float NuevaVelocidad);

	// NUEVA FUNCIÓN: Para que el proyectil ignore a un actor (el Jefe)
	void IgnorarActor(AActor* ActorParaIgnorar);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = "Componentes")
	class UStaticMeshComponent* MeshComponent;
};