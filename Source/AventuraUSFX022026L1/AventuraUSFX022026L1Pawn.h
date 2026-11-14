#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AventuraUSFX022026L1Pawn.generated.h"

UCLASS(Blueprintable)
class AAventuraUSFX022026L1Pawn : public APawn
{
	GENERATED_BODY()

public:
	AAventuraUSFX022026L1Pawn();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	FVector GunOffset;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Salud")
	float SaludJugador = 100.0f;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void FireShot(FVector FireDirection);
	void ShotTimerExpired();

	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName MoveUpBinding;
	static const FName TurnBinding;
	static const FName LookUpBinding;
	static const FName FireBinding;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	uint32 bCanFire : 1;
	FTimerHandle TimerHandle_ShotTimerExpired;
};