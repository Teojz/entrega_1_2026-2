#ifndef GESTORARCHIVOS_H
#ifndef GESTORARCHIVOS_H
#define GESTORARCHIVOS_H

#include <string>
#include "Jugador.h"

class GestorArchivos {
private:
    std::string rutaArchivo;

public:
    GestorArchivos();
    bool guardar(std::string ruta, Jugador* js, int numJ, int ronda, int lider);
    bool cargar(std::string ruta, Jugador*& js, int &numJ, int &ronda, int &lider);
};

#endif