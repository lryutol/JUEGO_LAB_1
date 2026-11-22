# Patrones de Diseño: Factory Method y Abstract Factory
### Programación Avanzada — 3er Semestre

---

## ¿Qué es Factory Method?

> Define una **interfaz para crear un objeto**, pero deja que las **subclases** decidan qué clase concreta instanciar.

El creador (clase padre) tiene un **método virtual** que las subclases sobreescriben para devolver el tipo correcto.

### Analogía
Un molde de galletas define la forma pero no el sabor. Cada fábrica concreta pone el sabor que quiere sin cambiar el molde.

---

## ¿Qué es Abstract Factory?

> Proporciona una interfaz para crear **familias de objetos relacionados** sin especificar sus clases concretas.

En vez de un solo método virtual, hay **varios** métodos virtuales, uno por cada tipo de objeto de la familia.

### Analogía
IKEA tiene un catálogo de habitaciones: si eliges "estilo moderno" te da mesa moderna + silla moderna + lámpara moderna. Si eliges "estilo rústico" te da los tres también, pero todos rústicos. La interfaz es la misma; la familia cambia.

---

## Diferencia clave

| | Factory Method | Abstract Factory |
|---|---|---|
| **Métodos virtuales** | 1 | N (varios) |
| **Qué crea** | 1 tipo de objeto | Familia de objetos relacionados |
| **Ejemplo en este juego** | `CrearPlataforma()` | `CrearEnemigo*()` × 3 |

---

## Implementación en el juego

### 1. Factory Method — `FabricaPlataformas`

```
FabricaPlataformas        ← Creador Abstracto
    └── CrearPlataforma() ← Factory Method (virtual puro)

AFabricaTerrestre         ← Creador Concreto #1
    └── CrearPlataforma() → new APlataformaTerrestre

AFabricaAcuatica          ← Creador Concreto #2
    └── CrearPlataforma() → new APlataformaAcuatica

AFabricaAerea             ← Creador Concreto #3
    └── CrearPlataforma() → new APlataformaAerea

AFabricaSubterranea       ← Creador Concreto #4
    └── CrearPlataforma() → new APlataformaSubterranea
```

**Archivo:** `FabricaPlataformas.h`, `FabricaTerrestre.h/.cpp`, etc.

---

### 2. Factory Method — `FabricaArmas` (C++ puro, sin Unreal macros)

```
FabricaArmas        ← Creador Abstracto
    └── CrearArma() ← Factory Method (virtual puro)

FabricaLaser        ← Creador Concreto #1
    └── CrearArma() → new ArmaLaser

FabricaMisil        ← Creador Concreto #2
    └── CrearArma() → new ArmaMisil

FabricaPlasma       ← Creador Concreto #3
    └── CrearArma() → new ArmaPlasma
```

**Archivo:** `FabricaArmas.h`, `FabricaArmas.cpp`

---

### 3. Factory Method — `FEstrategiaFactory` (variante estática)

Forma simple: método estático que recibe un parámetro y decide qué objeto crear.

```cpp
// Uso:
UEstrategiaAtaque* estrategia = FEstrategiaFactory::CrearEstrategia(fase);
```

**Archivo:** `EstrategiaFactory.h`, `EstrategiaFactory.cpp`

---

### 4. Abstract Factory — `AFabricaEnemigos`

```
AFabricaEnemigos              ← Fabrica Abstracta
    ├── CrearEnemigoAereo()   ← Factory Method 1
    ├── CrearEnemigoAcuatico()← Factory Method 2
    └── CrearEnemigoTerrestre()← Factory Method 3

AFabricaEnemigosNaturales     ← Fabrica Concreta #1 (familia natural)
    ├── CrearEnemigoAereo()   → Halcón
    ├── CrearEnemigoAcuatico()→ Pez
    └── CrearEnemigoTerrestre()→ Lobo

AFabricaEnemigosTecnologicos  ← Fabrica Concreta #2 (familia tecnológica)
    ├── CrearEnemigoAereo()   → Drone SciFi
    ├── CrearEnemigoAcuatico()→ Submarino
    └── CrearEnemigoTerrestre()→ Tanque
```

**Archivo:** `FabricaEnemigos.h`, `FabricaEnemigosNaturales.h/.cpp`, `FabricaEnemigosTecnologicos.h/.cpp`

---

### 5. Abstract Factory — `FabricaZona` (C++ puro, sin Unreal macros)

Crea un "kit completo de zona": un enemigo + una plataforma del mismo bioma.

```
FabricaZona                   ← Fabrica Abstracta
    ├── CrearEnemigoPrincipal()← Factory Method 1
    └── CrearPlataformaZona() ← Factory Method 2

FabricaZonaBosque             ← Fabrica Concreta #1
    ├── CrearEnemigoPrincipal()→ Lobo
    └── CrearPlataformaZona() → PlataformaTerrestre

FabricaZonaMarina             ← Fabrica Concreta #2
    ├── CrearEnemigoPrincipal()→ Pez
    └── CrearPlataformaZona() → PlataformaAcuatica

FabricaZonaAerea              ← Fabrica Concreta #3
    ├── CrearEnemigoPrincipal()→ Drone
    └── CrearPlataformaZona() → PlataformaAerea

FabricaZonaSubterranea        ← Fabrica Concreta #4
    ├── CrearEnemigoPrincipal()→ Tanque
    └── CrearPlataformaZona() → PlataformaSubterranea
```

**Archivo:** `FabricaZona.h`, `FabricaZona.cpp`

---

## Código de ejemplo — ¿Cómo se usa?

### Factory Method
```cpp
// Solo se trabaja con la interfaz (FabricaArmas), 
// no con la clase concreta (FabricaLaser)
FabricaArmas* fabrica = new FabricaLaser();
Arma* miArma = fabrica->ObtenerArmaLista();
miArma->Disparar(origen, direccion);
delete miArma;
delete fabrica;

// Cambiar de tipo de arma NO requiere modificar el código anterior:
fabrica = new FabricaMisil();
miArma = fabrica->ObtenerArmaLista();  // Mismo código, diferente objeto
```

### Abstract Factory
```cpp
// La función solo conoce FabricaZona (la interfaz abstracta)
void CrearZona(FabricaZona* fabrica, UWorld* mundo)
{
    // Crea los dos productos de la misma familia sin saber cuáles son
    fabrica->CrearEnemigoPrincipal(mundo, posEnemigo, rot);
    fabrica->CrearPlataformaZona(mundo, posPlataforma, rot);
}

// Uso:
CrearZona(new FabricaZonaBosque(),     mundo);  // lobo + terrestre
CrearZona(new FabricaZonaMarina(),     mundo);  // pez  + acuática
CrearZona(new FabricaZonaAerea(),      mundo);  // drone + aérea
CrearZona(new FabricaZonaSubterranea(),mundo);  // tanque + subterránea
// El cuerpo de CrearZona() no cambió en ningún caso ← clave del patrón
```

---

## Diagrama UML simplificado

```
         FACTORY METHOD                    ABSTRACT FACTORY
         ──────────────                    ────────────────

    FabricaArmas          AFabricaEnemigos
    + CrearArma()*        + CrearEnemigoAereo()*
         │                + CrearEnemigoAcuatico()*
    ┌────┴─────────┐      + CrearEnemigoTerrestre()*
    │              │             │
FabricaLaser  FabricaMisil  ┌───┴──────────────────┐
CrearArma()   CrearArma()   │                      │
→ ArmaLaser   → ArmaMisil  FabricaNaturales   FabricaTecnologicos
                            CrearEnemigo*()   CrearEnemigo*()
                            → Lobo/Pez/Halcón → Tanque/Sub/Drone
```

---

*Proyecto: AventuraUSFX022026L1 — Unreal Engine 4*
*Materia: Programación Avanzada, 3er Semestre*
