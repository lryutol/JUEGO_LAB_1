#pragma once

#include "CoreMinimal.h"
#include "NaveNodrizaBuilder.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"        // Necesario para UWorld
#include "Math/Vector.h"         // Necesario para FVector
#include "Math/Rotator.h"        // Necesario para FRotator

class ANaveNodriza;

class AVENTURAUSFX022026L1_API FDirectorNaveNodriza
{
public:
	// Receta 1: Nave de Asalto (mucho blindaje, torretas grandes)
	// Ahora recibe FNaveNodrizaBuilder por referencia
	static ANaveNodriza* ConstruirNaveDeAsalto(FNaveNodrizaBuilder& Builder, UWorld* World, FVector Loc, FRotator Rot)
	{
		UStaticMesh* MallaCasco = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		UStaticMesh* MallaMotor = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
		UStaticMesh* MallaTorreta = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));

		Builder.EnsamblarCasco(MallaCasco, FVector(8.0f, 12.0f, 3.0f));
		Builder.EnsamblarMotores(MallaMotor, FVector(2.0f, 2.0f, 4.0f));
		Builder.EnsamblarTorretas(MallaTorreta, FVector(2.0f, 2.0f, 3.0f));

		return Builder.Construir(World, Loc, Rot);
	}

	// Receta 2: Nave de Comando (más pequeña y rápida)
	static ANaveNodriza* ConstruirNaveDeComando(FNaveNodrizaBuilder& Builder, UWorld* World, FVector Loc, FRotator Rot)
	{
		UStaticMesh* MallaCasco = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		UStaticMesh* MallaMotor = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));

		Builder.EnsamblarCasco(MallaCasco, FVector(5.0f, 5.0f, 5.0f));
		Builder.EnsamblarMotores(MallaMotor, FVector(1.5f, 1.5f, 3.0f));

		return Builder.Construir(World, Loc, Rot);
	}
};