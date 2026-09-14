# entrega_1_2026-2 juego de cartas
Entrega del curso Estructura de datos

Proyecto desarrollado en C++
## Descripción del Proyecto
El sistema implementa un juego de mesa competitivo por turnos con soporte dinámico para $N$ jugadores (2, 3 o más). 

La baraja consta de 50 cartas numeradas estrictamente del 1 al 50, con asignación aleatoria y mutuamente excluyente de color (Rojo o Azul), garantizando que ningún identificador numérico o combinación se repita en la partida. El total de cartas se reparte equitativamente en memoria entre los jugadores configurados.

Durante cada ronda:
1. El jugador líder en turno define la condición de victoria (por ejemplo, "Rojo más alto").
2. Cada participante selecciona a ciegas una carta de su mano y la coloca en la mesa.
3. Las cartas se revelan y quien cumpla de forma óptima con la condición gana la totalidad de cartas jugadas en la mesa, sumándolas a su acumulado de puntos.
4. El sistema permite pausar y reanudar partidas en cualquier momento serializando el estado completo en un archivo de texto plano (`partida.txt`).

## Diagrama de Clases UML
![Diagrama UML](uml_diagrama.png)

## Funcionalidades Principales
- **Configuración Dinámica:** Admite partidas escalables para 2 o más jugadores reservando memoria en tiempo de ejecución (`Jugador*`, `Carta*`).
- **Baraja Exclusiva:** Algoritmo de inicialización que asegura unicidad matemática en el rango 1-50 y distribución de color.
- **Persistencia Completa:** Módulo `GestorArchivos` para guardar y cargar ronda, líder, manos restantes y puntajes.
- **Interfaz CLI:** Menú interactivo por consola con validaciones de entrada y visualización de mesa.

## Distribución de Actividades y Commits
- **[Nombre 1]:** Implementación de la clase `Carta`, algoritmo de barajado y generación sin duplicados del mazo de 50 elementos.
- **[Nombre 2]:** Clase `Jugador`, asignación dinámica de la mano (`Carta* mano`) y control de descarte/puntaje.
- **[Nombre 3]:** Clase `GestorArchivos`, serialización con `fstream` y parseo del archivo de guardado (`partida.txt`).
- **[Nombre 4]:** Clase controladora `Juego`, bucle principal de rondas dinámicas, evaluación de ganador y documentación del repositorio.

## Estructura del Archivo de Guardado (`partida.txt`)
```text
NUM_JUGADORES: 3
RONDA: 4
LIDER: 0
JUGADOR: 0 Juan PUNTOS: 6 CARTAS: 13
23 ROJO 45 AZUL 12 ROJO ...
JUGADOR: 1 Maria PUNTOS: 3 CARTAS: 13
14 AZUL 39 ROJO 02 AZUL ...
JUGADOR: 2 Pedro PUNTOS: 0 CARTAS: 13
05 ROJO 18 AZUL 49 ROJO ...
