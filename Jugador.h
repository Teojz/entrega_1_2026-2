#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Carta.h"

class Jugador {
private:
    int id;              // Identificador único del jugador
    std::string nombre;  // Nombre del jugador
    int puntaje;         // Puntos acumulados durante las rondas
    Carta* mano;         // Arreglo dinámico de objetos Carta
    int cantCartas;      // Cantidad de cartas en mano actualmente
    int capacidadMano;   // Capacidad máxima asignada al arreglo dinámico

public:
    // Constructores y Destructor
    Jugador();
    Jugador(int id, std::string nom, int maxCartas);
    ~Jugador(); // Libera la memoria dinámica asignada a la mano

    // Métodos del UML y auxiliares
    void recibirCarta(Carta c);
    Carta jugarCarta(int indice);
    void sumarPuntos(int pts);
    int getPuntaje() const;
    int getCantCartas() const;
    void mostrarMano() const;
    int getId() const;
    std::string getNombre() const;
    Carta getCarta(int indice) const; // Agregado para GestorArchivos
};

#endif // JUGADOR_H