#include "GestorArchivos.h"
#include <fstream>
#include <iostream>

GestorArchivos::GestorArchivos() : rutaArchivo("partida.txt") {}

// Serialización: Guarda el estado completo de la partida en el archivo especificado
bool GestorArchivos::guardar(std::string ruta, Jugador* js, int numJ, int ronda, int lider) {
    std::string nombreArchivo = ruta.empty() ? rutaArchivo : ruta;
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar: " << nombreArchivo << std::endl;
        return false;
    }

    // 1. Guardar encabezados globales de la partida
    archivo << "NUM_JUGADORES: " << numJ << "\n";
    archivo << "RONDA: " << ronda << "\n";
    archivo << "LIDER_ACTUAL: " << lider << "\n";

    // 2. Guardar la información de cada jugador y sus cartas
    for (int i = 0; i < numJ; i++) {
        archivo << "JUGADOR: " << js[i].getId() << " " 
                << js[i].getNombre() << " "
                << "PUNTOS: " << js[i].getPuntaje() << " "
                << "CARTAS: " << js[i].getCantCartas() << "\n";

        // Volcado automático de las cartas del jugador
        for (int c = 0; c < js[i].getCantCartas(); c++) {
            archivo << js[i].getCarta(c).getNumero() << " " 
                    << js[i].getCarta(c).getColor() << " ";
        }
        
        archivo << "\n"; 
    }

    archivo.close();
    return true;
}

// Deserialización: Carga el estado guardado y reconstruye los objetos en memoria
bool GestorArchivos::cargar(std::string ruta, Jugador*& js, int &numJ, int &ronda, int &lider) {
    std::string nombreArchivo = ruta.empty() ? rutaArchivo : ruta;
    std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para cargar: " << nombreArchivo << std::endl;
        return false;
    }

    std::string etiqueta;

    // 1. Leer encabezados globales
    archivo >> etiqueta >> numJ;   // NUM_JUGADORES: X
    archivo >> etiqueta >> ronda;  // RONDA: Y
    archivo >> etiqueta >> lider;  // LIDER_ACTUAL: Z

    // 2. Crear dinámicamente el arreglo de Jugadores en el Heap
    if (js != nullptr) {
        delete[] js; // Previene fugas de memoria si ya existía un arreglo
    }
    js = new Jugador[numJ];

    // 3. Leer cada jugador y reconstruir su mano
    for (int i = 0; i < numJ; i++) {
        int id, puntos, cantCartas;
        std::string nombre, etiquetaPuntos, etiquetaCartas;

        // Leer encabezado: JUGADOR: [id] [nombre] PUNTOS: [puntos] CARTAS: [cantCartas]
        archivo >> etiqueta >> id >> nombre >> etiquetaPuntos >> puntos >> etiquetaCartas >> cantCartas;

        // Instanciar jugador pasando la cantidad de cartas como capacidad inicial
        js[i] = Jugador(id, nombre, cantCartas);
        js[i].sumarPuntos(puntos);

        // Leer cada par (numero color) y cargar las cartas en la mano
        for (int c = 0; c < cantCartas; c++) {
            int numCarta;
            std::string colorCarta;
            archivo >> numCarta >> colorCarta;
            js[i].recibirCarta(Carta(numCarta, colorCarta));
        }
    }

    archivo.close();
    return true;
}