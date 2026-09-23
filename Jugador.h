
#include <iostream>
using namespace std;

class Jugador {
private:
	int id;
	string nombre;
	int puntaje;
	Carta* mano;
	int cantCartas

public:
	Jugador();
	Jugador(int id,string nom,int maxCartas);
	~Jugador(); // Para liberar la memoria dinamica asignada a la mano
	void recibirCarta(Carta c);
	Carta jugarCarta(int indice);
	void sumarPuntos(int pts);
	int getPuntaje();
	int getCantCartas();
	void mostrarMano();
}