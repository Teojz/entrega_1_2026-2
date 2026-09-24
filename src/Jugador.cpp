#include "Jugador.h"
#include <iostream>

// Constructor por defecto
Jugador::Jugador() 
    : id(0), nombre(""), puntaje(0), mano(nullptr), cantCartas(0), capacidadMano(0) {}

// Constructor parametrizado: Asigna memoria dinámica en el Heap para la mano
Jugador::Jugador(int id, std::string nom, int maxCartas) 
    : id(id), nombre(nom), puntaje(0), cantCartas(0), capacidadMano(maxCartas) {
    if (maxCartas > 0) {
        mano = new Carta[maxCartas]; // Asignación de memoria dinámica
    } else {
        mano = nullptr;
    }
}

// Constructor de copia (Copia Profunda / Deep Copy)
Jugador::Jugador(const Jugador& otro) 
    : id(otro.id), nombre(otro.nombre), puntaje(otro.puntaje), 
      cantCartas(otro.cantCartas), capacidadMano(otro.capacidadMano) {
    if (otro.capacidadMano > 0 && otro.mano != nullptr) {
        mano = new Carta[otro.capacidadMano];
        for (int i = 0; i < otro.cantCartas; i++) {
            mano[i] = otro.mano[i];
        }
    } else {
        mano = nullptr;
    }
}

// Operador de asignación (Copia Profunda / Deep Copy)
Jugador& Jugador::operator=(const Jugador& otro) {
    if (this != &otro) { // Evitar autoasignación (ej. j1 = j1)
        // 1. Liberar la memoria previa si existía
        if (mano != nullptr) {
            delete[] mano;
        }

        // 2. Copiar atributos simples
        this->id = otro.id;
        this->nombre = otro.nombre;
        this->puntaje = otro.puntaje;
        this->cantCartas = otro.cantCartas;
        this->capacidadMano = otro.capacidadMano;

        // 3. Asignar nueva memoria propia
        if (otro.capacidadMano > 0 && otro.mano != nullptr) {
            this->mano = new Carta[otro.capacidadMano];
            for (int i = 0; i < otro.cantCartas; i++) {
                this->mano[i] = otro.mano[i];
            }
        } else {
            this->mano = nullptr;
        }
    }
    return *this;
}

// Destructor: Libera la memoria dinámica asignada para evitar memory leaks
Jugador::~Jugador() {
    if (mano != nullptr) {
        delete[] mano;
        mano = nullptr;
    }
}

// Agrega una carta al arreglo dinámico
void Jugador::recibirCarta(Carta c) {
    if (cantCartas < capacidadMano && mano != nullptr) {
        mano[cantCartas] = c;
        cantCartas++;
    } else {
        std::cout << "La mano de " << nombre << " esta llena o no inicializada.\n";
    }
}

// Remueve una carta de la mano según su índice y reorganiza el arreglo
Carta Jugador::jugarCarta(int indice) {
    if (indice < 0 || indice >= cantCartas) {
        std::cout << "Indice de carta invalido.\n";
        return Carta(); // Retorna carta por defecto
    }

    Carta cartaJugada = mano[indice];

    // Desplazar las cartas restantes para no dejar huecos en el arreglo
    for (int i = indice; i < cantCartas - 1; i++) {
        mano[i] = mano[i + 1];
    }

    cantCartas--; // Se reduce la cantidad actual de cartas
    return cartaJugada;
}

// Incrementa el puntaje acumulado
void Jugador::sumarPuntos(int pts) {
    this->puntaje += pts;
}

// Getters
int Jugador::getPuntaje() const {
    return puntaje;
}

int Jugador::getCantCartas() const {
    return cantCartas;
}

int Jugador::getId() const {
    return id;
}

std::string Jugador::getNombre() const {
    return nombre;
}

// Muestra en consola la lista de cartas actuales en la mano
void Jugador::mostrarMano() const {
    std::cout << "Mano de " << nombre << " (Puntos: " << puntaje << "):\n";
    for (int i = 0; i < cantCartas; i++) {
        std::cout << "[" << i << "] ";
        mano[i].mostrarInfo();
    }
}

Carta Jugador::getCarta(int indice) const {
    if (indice >= 0 && indice < cantCartas) {
        return mano[indice]; // Retorna una copia de la carta sin borrarla de la mano
    }
    return Carta(); // Retorna carta por defecto si el índice no es válido
}