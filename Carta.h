#ifndef CARTA_H
#define CARTA_H

#include <string>

class Carta {
private:
    int numero;
    std::string color;

public:

    Carta();
    Carta(int num, const std::string& col);

    // Getters
    int getNumero() const;
    std::string getColor() const;

    void mostrarInfo() const;
};

#endif // CARTA_H