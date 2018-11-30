#pragma once

#include "../../CatanGame/CatanGame.h"
#include "../../CatanNetworking/CatanNetworking.h"

#include <string>

using namespace std;

/*
* CatanContext - Contiene la informacion de contexto del funcionamiento
* del programa para el flujo general del mismo, permite de esa forma
* que se comuniquen las partes del mismo. Hace las veces de la informacion
* que intercambian los objetos que hacen a la esfera mas alta del juego.
*/
class CatanContext {

public:

	/*
	* CatanContext - Se construyo por defecto y se inicializa
	* con estado inicial de todas sus partes
	*/
	CatanContext();

	/*
	* Getters y setters
	*/
	void setUsername(string name);
	void setIp(string ip);
	void setPort(unsigned int port);

	string getUsername(void);
	string getIp(void);
	unsigned int getPort(void);

	CatanGame& getGame(void);
	CatanNetworking& getNetworking(void);

private:
	string username;
	string ip;
	unsigned int port;

	CatanGame game;
	CatanNetworking networking;
};