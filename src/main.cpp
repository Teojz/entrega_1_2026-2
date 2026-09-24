#include "../include/Juego.h"
#include <iostream>

int main() {
    int opcion = 0;

    std::cout << "=============================================\n";
    std::cout << "    JUEGO DE CARTAS POR COLORES Y NUMEROS    \n";
    std::cout << "=============================================\n";
    std::cout << "1. Iniciar nueva partida\n";
    std::cout << "2. Cargar partida guardada\n";
    std::cout << "3. Salir\n";
    std::cout << "Seleccione una opcion: ";
    std::cin >> opcion;

    if (opcion == 1) {
        int n;
        std::cout << "Ingrese la cantidad de jugadores (2 o mas): ";
        std::cin >> n;
        while (n < 2 || n > 50) {
            std::cout << "Numero invalido. Ingrese entre 2 y 50: ";
            std::cin >> n;
        }
        Juego partida(n);
        partida.ejecutar();
    } else if (opcion == 2) {
        Juego partida;
        if (partida.cargarPartida("partida.txt")) {
            partida.ejecutar();
        }
    } else {
        std::cout << "Saliendo del juego...\n";
    }

    return 0;
}