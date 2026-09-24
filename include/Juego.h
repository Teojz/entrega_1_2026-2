#ifndef JUEGO_H
#define JUEGO_H

#include "Carta.h"
#include "Jugador.h"
#include "GestorArchivos.h"
#include <string>

class Juego {
private:
    int numJugadores;
    int cartasPorJugador;
    Jugador* jugadores;
    Carta mazo[50];
    Carta* mesa;
    int rondaActual;
    int jugadorLider;
    GestorArchivos gestor;

public:
    // Constructor y destructor
    Juego();
    Juego(int nJugadores);
    ~Juego();

    // Métodos del diagrama UML
    void inicializarMazo();
    void barajarYRepartir();
    void jugarRonda();
    int evaluarGanadorRonda(const std::string& condicionColor);
    void guardarPartida(const std::string& ruta);
    bool cargarPartida(const std::string& ruta);
    void ejecutar();
};

#endif // JUEGO_H