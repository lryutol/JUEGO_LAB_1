# JUEGO_LAB_1 - Proyecto Unreal Engine 4.27

Este proyecto es un juego de naves en tercera persona (TwinStick Shooter) desarrollado en **Unreal Engine 4.27** y **C++**, cuyo objetivo principal es la implementación práctica de **Patrones de Diseño de Software**.

## 🧩 Patrones de Diseño Implementados

1. **Builder**: Utilizado para ensamblar paso a paso a los enemigos (`FEnemigoBuilder`), separando su construcción de su representación final.
2. **Abstract Factory**: Implementado en las fábricas de enemigos (`FabricaEnemigosNaturales` y `FabricaEnemigosTecnologicos`) para crear familias de enemigos con estilos visuales y estadísticas coherentes.
3. **Facade**: La clase `FachadaJuego` oculta la complejidad de crear el nivel, las plataformas y las formaciones de enemigos, dándole al GameMode una interfaz simple.
4. **Observer**: Utilizado en las `Torretas` (Publisher) y los enemigos (Observers) para alertar dinámicamente sobre la posición del jugador.
5. **Strategy**: Implementado en el Jefe (`AJefe`) para cambiar sus algoritmos de ataque en tiempo de ejecución (proyectiles básicos, gigantes, invocación de drones, abanicos y redes) sin modificar su clase base.

## ⚙️ Características de Gameplay
* **Jefe Final dinámico**: Cambia de estrategia según su vida (50% y 10%) y la destrucción de torretas.
* **Movimiento 3D**: La nave del jugador se mueve en los ejes X, Y y Z, con una cámara de persecución.
* **Caos enemigo**: Al destruir todas las torretas, los enemigos pierden su patrón de movimiento y comienzan a atacar de forma errática.

## 🚀 Cómo ejecutar
1. Clona el repositorio.
2. Haz clic derecho en `AventuraUSFX022026L1.uproject` y genera los archivos de Visual Studio.
3. Compila el proyecto en Visual Studio 2022.
4. Abre el `.uproject` y dale a Play.

---
*Desarrollado como proyecto académico.*
