#include "AventuraUSFX022026L1Pawn.h"
#include "AventuraUSFX022026L1Projectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

const FName AAventuraUSFX022026L1Pawn::MoveForwardBinding("MoveForward");
const FName AAventuraUSFX022026L1Pawn::MoveRightBinding("MoveRight");
const FName AAventuraUSFX022026L1Pawn::MoveUpBinding("MoveUp");
const FName AAventuraUSFX022026L1Pawn::TurnBinding("Turn");
const FName AAventuraUSFX022026L1Pawn::LookUpBinding("LookUp");
const FName AAventuraUSFX022026L1Pawn::FireBinding("Fire");

AAventuraUSFX022026L1Pawn::AAventuraUSFX022026L1Pawn()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	if (ShipMesh.Succeeded()) ShipMeshComponent->SetStaticMesh(ShipMesh.Object);

	// CORRECCIÓN: Hacemos que la nave ignore a otros Pawns (enemigos/jefe) para no atascarse
	ShipMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	if (FireAudio.Succeeded()) FireSound = FireAudio.Object;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(false);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	MoveSpeed = 1500.0f;
	GunOffset = FVector(150.f, 0.f, 0.f);
	FireRate = 0.15f;
	bCanFire = true;
}

void AAventuraUSFX022026L1Pawn::BeginPlay()
{
	Super::BeginPlay();

	if (CameraBoom)
	{
		CameraBoom->SetUsingAbsoluteRotation(false);
		CameraBoom->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
		CameraBoom->TargetArmLength = 800.f;
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetViewTargetWithBlend(this, 0.0f);
	}
}

void AAventuraUSFX022026L1Pawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(MoveUpBinding);
	PlayerInputComponent->BindAxis(TurnBinding);
	PlayerInputComponent->BindAxis(LookUpBinding);
	PlayerInputComponent->BindAxis(FireBinding);
}

void AAventuraUSFX022026L1Pawn::Tick(float DeltaSeconds)
{
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);
	const float UpValue = GetInputAxisValue(MoveUpBinding);
	const float TurnValue = GetInputAxisValue(TurnBinding);
	const float LookUpValue = GetInputAxisValue(LookUpBinding);

	if (TurnValue != 0.0f || LookUpValue != 0.0f)
	{
		AddActorLocalRotation(FRotator(-LookUpValue, TurnValue, 0.0f));
	}

	const FVector MoveDirection = FVector(ForwardValue, RightValue, UpValue).GetClampedToMaxSize(1.0f);
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FVector LocalMovement = GetActorRotation().RotateVector(Movement);
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(LocalMovement, GetActorRotation(), true, &Hit);
	}

	const float FireValue = GetInputAxisValue(FireBinding);
	if (FireValue > 0.0f)
	{
		FireShot(GetActorForwardVector());
	}
}

void AAventuraUSFX022026L1Pawn::FireShot(FVector FireDirection)
{
	if (bCanFire == true)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters Params;
			Params.Owner = this;
			World->SpawnActor<AAventuraUSFX022026L1Projectile>(SpawnLocation, FireRotation, Params);
		}

		bCanFire = false;
		World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AAventuraUSFX022026L1Pawn::ShotTimerExpired, FireRate);

		if (FireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}
	}
}

void AAventuraUSFX022026L1Pawn::ShotTimerExpired()
{
	bCanFire = true;
}

float AAventuraUSFX022026L1Pawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	SaludJugador -= DamageAmount;
	UE_LOG(LogTemp, Error, TEXT("VIDA JUGADOR: %f"), SaludJugador);
	return DamageAmount;
}