#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EstadoNaveNodriza.generated.h"

class ANaveNodriza;

UCLASS(Abstract)
class AVENTURAUSFX022026L1_API UEstadoNaveNodriza : public UObject
{
	GENERATED_BODY()
public:
	virtual void Entrar(ANaveNodriza* Nave) {}
	virtual void Tick(ANaveNodriza* Nave, float DeltaTime) {}
};

// ESTADO 1: NORMAL (Vida > 50%)
UCLASS()
class AVENTURAUSFX022026L1_API UEstadoNaveNormal : public UEstadoNaveNodriza
{
	GENERATED_BODY()
public:
	virtual void Tick(ANaveNodriza* Nave, float DeltaTime) override;
};

// ESTADO 2: AVERIADA (Vida <= 50%)
UCLASS()
class AVENTURAUSFX022026L1_API UEstadoNaveAveriada : public UEstadoNaveNodriza
{
	GENERATED_BODY()
public:
	virtual void Entrar(ANaveNodriza* Nave) override;
	virtual void Tick(ANaveNodriza* Nave, float DeltaTime) override;
};

// ESTADO 3: CRÍTICA (Vida <= 10%)
UCLASS()
class AVENTURAUSFX022026L1_API UEstadoNaveCritica : public UEstadoNaveNodriza
{
	GENERATED_BODY()
public:
	virtual void Entrar(ANaveNodriza* Nave) override;
	virtual void Tick(ANaveNodriza* Nave, float DeltaTime) override;
};