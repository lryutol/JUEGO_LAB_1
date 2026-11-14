#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EstrategiaAtaque.generated.h"

class AJefe;

UCLASS(Abstract)
class AVENTURAUSFX022026L1_API UEstrategiaAtaque : public UObject
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) {}
};

UCLASS()
class AVENTURAUSFX022026L1_API UEAtaqueBasico : public UEstrategiaAtaque
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) override;
};

UCLASS()
class AVENTURAUSFX022026L1_API UEAtaquePesado : public UEstrategiaAtaque
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) override;
};

UCLASS()
class AVENTURAUSFX022026L1_API UEAtaqueInvocar : public UEstrategiaAtaque
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) override;
};

UCLASS()
class AVENTURAUSFX022026L1_API UEAtaqueAbanico : public UEstrategiaAtaque
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) override;
};

UCLASS()
class AVENTURAUSFX022026L1_API UEAtaqueRed : public UEstrategiaAtaque
{
	GENERATED_BODY()
public:
	virtual void Atacar(AJefe* Jefe) override;
};