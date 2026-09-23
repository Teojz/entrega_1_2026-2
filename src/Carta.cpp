#include "../include/Carta.h"
#include <iostream>

// Constructor por defecto
Carta::Carta() : numero(0), color("Sin Color") {}

// Constructor parametrizado
Carta::Carta(int num, const std::string& col) : numero(num), color(col) {}

// Retorna el valor numerico de la carta
int Carta::getNumero() const {
    return numero;
}

// Retorna el color de la carta ("Rojo" o "Azul")
std::string Carta::getColor() const {
    return color;
}

// Imprime en consola el formato de la carta
void Carta::mostrarInfo() const {
    std::cout << "[" << color << " " << numero << "]\n";
}