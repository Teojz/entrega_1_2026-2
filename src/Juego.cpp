#include "../include/Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Constructor por defecto
Juego::Juego() 
    : numJugadores(0), cartasPorJugador(0), jugadores(nullptr), mesa(nullptr), 
      rondaActual(1), jugadorLider(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Constructor parametrizado
Juego::Juego(int nJugadores) 
    : numJugadores(nJugadores), rondaActual(1), jugadorLider(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    if (numJugadores > 0) {
        cartasPorJugador = 50 / numJugadores;
        jugadores = new Jugador[numJugadores];
        mesa = new Carta[numJugadores];

        for (int i = 0; i < numJugadores; i++) {
            jugadores[i] = Jugador(i, "Jugador_" + std::to_string(i + 1), cartasPorJugador);
        }
    } else {
        cartasPorJugador = 0;
        jugadores = nullptr;
        mesa = nullptr;
    }
}

// Destructor para evitar fugas de memoria en el Heap
Juego::~Juego() {
    if (jugadores != nullptr) {
        delete[] jugadores;
        jugadores = nullptr;
    }
    if (mesa != nullptr) {
        delete[] mesa;
        mesa = nullptr;
    }
}

// Genera las 50 cartas únicas (números 1 al 50 asignados aleatoriamente a Rojo o Azul)
void Juego::inicializarMazo() {
    for (int i = 0; i < 50; i++) {
        int numero = i + 1;
        std::string color = (std::rand() % 2 == 0) ? "Rojo" : "Azul";
        mazo[i] = Carta(numero, color);
    }
}

// Baraja el mazo con algoritmo Fisher-Yates y reparte a cada participante
void Juego::barajarYRepartir() {
    for (int i = 49; i > 0; i--) {
        int j = std::rand() % (i + 1);
        std::swap(mazo[i], mazo[j]);
    }

    int indiceMazo = 0;
    for (int c = 0; c < cartasPorJugador; c++) {
        for (int j = 0; j < numJugadores; j++) {
            jugadores[j].recibirCarta(mazo[indiceMazo++]);
        }
    }
}

// Evalúa quién cumple la condición del color solicitado con el número más alto
int Juego::evaluarGanadorRonda(const std::string& condicionColor) {
    int idGanador = -1;
    int maxNumero = -1;

    for (int i = 0; i < numJugadores; i++) {
        if (mesa[i].getColor() == condicionColor) {
            if (mesa[i].getNumero() > maxNumero) {
                maxNumero = mesa[i].getNumero();
                idGanador = i;
            }
        }
    }

    // Si nadie tuvo el color solicitado, retiene el turno el líder inicial
    if (idGanador == -1) {
        idGanador = jugadorLider;
    }

    return idGanador;
}

// Ejecuta una ronda completa de juego
void Juego::jugarRonda() {
    std::cout << "\n============================================\n";
    std::cout << "               RONDA " << rondaActual << "\n";
    std::cout << " Líder del turno: " << jugadores[jugadorLider].getNombre() << "\n";
    std::cout << "============================================\n";

    // 1. El líder inspecciona su mano y escoge el reto
    jugadores[jugadorLider].mostrarMano();
    int eleccionColor;
    std::cout << "\nLíder, elija el color del reto (1: Rojo, 2: Azul): ";
    std::cin >> eleccionColor;
    std::string colorReto = (eleccionColor == 1) ? "Rojo" : "Azul";
    std::cout << ">> RETO DE LA RONDA: " << colorReto << " más alto <<\n\n";

    // 2. Cada jugador coloca o descarta su carta
    for (int i = 0; i < numJugadores; i++) {
        int turno = (jugadorLider + i) % numJugadores;
        std::cout << "\n--- Turno de " << jugadores[turno].getNombre() << " ---\n";

        if (jugadores[turno].tieneColor(colorReto)) {
            jugadores[turno].mostrarMano();
            int idx;
            do {
                std::cout << "Seleccione el índice de la carta [" << colorReto << "] a jugar: ";
                std::cin >> idx;
            } while (idx < 0 || idx >= jugadores[turno].getCantCartas() || 
                     jugadores[turno].getCarta(idx).getColor() != colorReto);

            mesa[turno] = jugadores[turno].jugarCarta(idx);
        } else {
            // Penalización: no tiene el color pedido, descarta una carta forzada y no compite
            std::cout << "[!] No tienes cartas de color " << colorReto << ".\n";
            std::cout << "Penalización: se descartará tu primera carta automáticamente y no puntúas.\n";
            mesa[turno] = jugadores[turno].jugarCarta(0); 
        }
    }

    // 3. Revelar cartas sobre la mesa
    std::cout << "\n--- CARTAS EN LA MESA ---\n";
    for (int i = 0; i < numJugadores; i++) {
        std::cout << jugadores[i].getNombre() << " jugó: ";
        mesa[i].mostrarInfo();
    }

    // 4. Determinar ganador y asignar puntos
    int ganador = evaluarGanadorRonda(colorReto);
    int puntosRonda = numJugadores; // Suma todas las cartas puestas en la mesa
    jugadores[ganador].sumarPuntos(puntosRonda);

    std::cout << "\n>>> ¡" << jugadores[ganador].getNombre() 
              << " gana la ronda con la mejor carta y obtiene " 
              << puntosRonda << " puntos! <<<\n";

    // 5. El ganador asume o retiene el liderazgo para la próxima ronda
    jugadorLider = ganador;
    rondaActual++;
}

void Juego::guardarPartida(const std::string& ruta) {
    gestor.guardar(ruta, jugadores, numJugadores, rondaActual, jugadorLider);
}

bool Juego::cargarPartida(const std::string& ruta) {
    if (gestor.cargar(ruta, jugadores, numJugadores, rondaActual, jugadorLider)) {
        if (mesa != nullptr) delete[] mesa;
        mesa = new Carta[numJugadores];
        if (numJugadores > 0) {
            cartasPorJugador = jugadores[0].getCantCartas();
        }
        return true;
    }
    return false;
}

// Bucle principal de ejecución
void Juego::ejecutar() {
    inicializarMazo();
    barajarYRepartir();

    while (jugadores[0].getCantCartas() > 0) {
        jugarRonda();

        char opcion;
        std::cout << "\n¿Desea guardar y salir? (s/n): ";
        std::cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            guardarPartida("partida.txt");
            std::cout << "Partida guardada. ¡Hasta pronto!\n";
            return;
        }
    }

    // Fin de la partida
    std::cout << "\n============================================\n";
    std::cout << "             FIN DEL JUEGO                  \n";
    std::cout << "============================================\n";
    int maxPts = -1;
    int idCampeon = 0;
    for (int i = 0; i < numJugadores; i++) {
        std::cout << jugadores[i].getNombre() << " - Puntos finales: " << jugadores[i].getPuntaje() << "\n";
        if (jugadores[i].getPuntaje() > maxPts) {
            maxPts = jugadores[i].getPuntaje();
            idCampeon = i;
        }
    }
    std::cout << "\n>>> ¡EL GANADOR ES " << jugadores[idCampeon].getNombre() << " CON " << maxPts << " PUNTOS! <<<\n";
}