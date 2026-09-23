#include "Jugador.h"
#include <iostream>

// Constructor por defecto
Jugador::Jugador()
	: id(0), nombre(""), puntaje(0), mano(nullptr), cantCartas(0), capacidadMano(0) {}

// Constructor parametrizado: Asigna memoria dinamica para la mano
Jugador::Jugador(int id, std::string nom, int maxCartas)
	: id(id), nombre(nom), puntaje(0), cantCartas(0), capacidadMano(maxCartas) {
	if (maxCartas > 0) {
		mano = new Carta[maxCartas]; // Asignacion de memoria dinamica
	} else {
		mano = nullptr;
	}
}

// Destructor: Libera la memoria dinamica asignada para evitar memory leaks
Jugador::~Jugador() {
	if (mano != nullptr) {
		delete[] mano;
		mano = nullptr;
	}
}

// Agrega una carta al arreglo dinamico
void Jugador::recibirCarta(Carta c) {
	if (cantCartas < capacidadMano && mano != nullptr) {
		mano[cantCartas] = c;
		cantCartas++;
	} else {
		std::cout << "La mano de " << nombre << " esta llena o no inicializada.\n";
	}
}

// Remueve una carta de la mano segun su indice y reorganiza el arreglo
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


// Muestra en consola la lista de cartas actuales en la mano
void Jugador::mostrarMano() const {
	std::cout << "Mano de " << nombre << " (Puntos: " << puntaje << "):\n";
	for (int i = 0; i < cantCartas; i++) {
		std::cout << "[" << i << "] ";
		mano[i].mostrarInfo();
	}
}



// Verifica si el jugador posee al menos una carta del color solicitado

//NO ESTA EN EL DIAGRAMA PERO SE PUEDE IMPLEMENTAR

bool Jugador::tieneColor(const std::string& color) const {
	for (int i = 0; i < cantCartas; i++) {
		if (mano[i].getColor() == color) {
			return true;
		}
	}
	return false;
}