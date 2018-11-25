#pragma once

#include <string>

using namespace std;

#define NON_PLACE	"FFF"

using MapValue = unsigned char;

/*
* ResourceId
* Identificadores de cada tipo de recurso en el juego.
*/
enum class ResourceId : MapValue {
	FOREST = 0x4D,
	HILL = 0x4C,
	MOUNTAIN = 0x50,
	FIELD = 0x54,
	PASTURES = 0x4F,
	DESERT = 0x4E
};

/*
* SeaId
* Identificadores de los tipos de puertos en cada mar del mapa.
*/
enum class SeaId : MapValue {
	NORMAL = 'N',	// Cambia 3 cartas por 1
	WHEAT = 'T',	// Cambia 3 cartas por 1, o 2 trigos por 1
	SHEEP = 'O',	// Cambia 3 cartas por 1, o 2 ovejas por 1
	BRICK = 'L',	// Cambia 3 cartas por 1, o 2 ladrillos por 1
	STONE = 'P',	// Cambia 2 piedras por 1
	WOOD = 'M',		// Cambia 2 maderas por 1
};

/*
* DevCardId
* Identificadores de las cartas de desarrollo.
*/
enum class DevCardId : unsigned char {
	KNIGHT = 'K',
	VICTORY_POINT = 'V',
	ROAD_BUILD = 'C',
	MONOPOLY = 'M',
	YEARS_OF_PLENTY = 'P'
};

/*
* Funciones de verificacion de valores
*/
bool isMapValue(unsigned char value);
bool isSeaValue(unsigned char value);
bool isResourceValue(unsigned char value);
bool isValidToken(unsigned char value);
bool isDevCard(unsigned char value);
bool isValidDice(unsigned char value);
bool isMapPosition(unsigned char value);
bool isSeaPosition(unsigned char value);

/*
* matchCoords
* Devuelve true en el caso de que las dos coordenadas hagan referencia al mismo lugar
*/
bool matchCoords(string str1, string str2);

/*
* CatanData
* Clase base para datos o informacion contenida durante el juego,
* ya sea en paquetes de datos intercambiados por networking o bien
* que se utilizan como eventos para el flujo interno de la logica.
*/
class CatanData {
public:

	/* 
	* Type
	* Tipos de datos implementados posteriormente en Catan
	*/
	enum Type : unsigned int {BANK, BUILDING, CARD_IS, DEV_CARDS, DICES, KNIGHT, MAP,
		MONOPOLY, NAME, OFFER, ROBBER_CARDS, ROBBER_MOVE, TOKEN, YOP};

	/* Constructor */
	CatanData(Type _type) : type(_type) {}

	/*
	* getType
	* Devuelve el tipo de CatanData implementado
	*/
	Type getType(void) { return this->type; }

private:
	Type type;
};