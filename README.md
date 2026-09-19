# entrega_1_2026-2 juego de cartas
Entrega del curso Estructura de datos
Proyecto desarrollado en C++ 

$Proyecto$ desarrollado en C++ 

# Descripción del Proyecto
El sistema modela un juego de cartas por turnos con capacidad para $N$ jugadores (2, 3 o más).

# Baraja y Reparto
La baraja se compone de 50 cartas numeradas estrictamente del 1 al 50. A cada número se le asigna de forma aleatoria y única el color Rojo o Azul, impidiendo duplicados tanto de valor como de combinación color-número. Las cartas se barajan y se reparten equitativamente entre los participantes en memoria dinámica.

# Mecánica de Juego y Reglas de Turno
1. **Inspección de mano:** Todos los jugadores visualizan sus propias cartas.
2. **Declaración del Reto:** El jugador activo (líder) examina sus cartas y establece una condición retando a los demás a superarlo (por ejemplo: *"Rojos más altos"*).
3. **Validación de Color y Penalización:**
   - Si un participante **posee** cartas del color solicitado, escoge estratégicamente cuál jugar para competir por la condición.
   - Si un participante **no posee cartas del color solicitado** (por ejemplo, le pidieron Azul y solo tiene Rojas), queda inhabilitado para competir en la ronda, pierde obligatoriamente una carta de su mano como penalización por descarte y no suma puntos.
4. **Resolución:**
   - Las cartas en competencia se evalúan contra la condición impuesta.
   - Si el retador inicial mantiene la mejor carta, gana la totalidad de cartas jugadas a la mesa (incluyendo las descartadas por penalización), suma los puntos correspondientes y retiene el turno para volver a retar.
   - Si otro participante supera al líder, dicho jugador reclama el pozo de cartas de la mesa, suma los puntos y arrebata el liderazgo para definir la siguiente ronda.
5. **Cierre de Partida:** El juego finaliza cuando los participantes agotan sus cartas. Gana el jugador con mayor puntaje acumulado.

# Persistencia
El sistema permite guardar el estado de la partida en cualquier momento en un archivo (`partida.txt`) y reanudarla posteriormente, manteniendo ronda, líder activo, manos restantes y puntajes.

## Diagrama de Clases UML
<img width="982" height="898" alt="Diagrama UML" src="https://github.com/user-attachments/assets/42583af6-52a5-49fd-bb4f-6c1f752033f2" />


## Funcionalidades Principales
- **Memoria Dinámica:** Creación y gestión de $N$ jugadores y manos variables en el heap mediante punteros (`Jugador*`, `Carta*`).
- **Control de Restricciones:** Validación de color en mano (`tieneColor`) y flujo de descarte forzoso.
- **Persistencia (I/O):** Módulo `GestorArchivos` con soporte para lectura/escritura mediante `fstream`.
- **Mazo Exclusivo:** Generación matemática sin colisiones de identificadores o colores.

## Distribución de Actividades y Commits
- **[Teojz]:** Clase `Carta`, algoritmo de barajado y generación del mazo único de 50 elementos.
- **[Carlos10marin]:** Clase `Jugador`, administración de la mano en memoria dinámica, validación de color y método de descarte forzado.
- **[Carlos10marin]:** Clase `GestorArchivos`, serialización y deserialización del estado de partida (`partida.txt`).
- **[Teojz]:** Clase controladora `Juego`, lógica de apuestas/penalizaciones, rotación de liderazgo y documentación del repositorio.

#Formato del Archivo de Guardado (`partida.txt`)
```text
NUM_JUGADORES: 3
RONDA: 5
LIDER_ACTUAL: 2
JUGADOR: 0 Carlos PUNTOS: 8 CARTAS: 10
12 ROJO 45 ROJO 03 ROJO ...
JUGADOR: 1 Lucia PUNTOS: 4 CARTAS: 11
22 AZUL 15 ROJO 38 AZUL ...
JUGADOR: 2 Mateo PUNTOS: 12 CARTAS: 10
01 AZUL 49 AZUL 19 ROJO ...
