#pragma once

/*
* ACLARACION: Recordar que la definicion base de NetworkPacket es utilizada
* tambien por todos los paquetes de datos compuestos unicamente por un header,
* no asi con aquellos que portan mayor informacion, para quienes se definira
* clase que herede de NetworkPacket, como NamePacket, TokenPacket... etc.
*
* Mientras que mensajes como ACK, NAME, YES.... seran reutilizacion de la
* clase base directamente.
*/

/* 
* PacketHeader
* Define los diferentes tipos de encabezados que pueden
* constituir a un mensaje o paquete de datos, para clasificar
* el tipo del mismo.
*/
enum class PacketHeader : unsigned char {
	ACK = 0x01,
	NAME = 0x10,
	NAME_IS,
	MAP_IS,
	CIRCULAR_TOKENS,
	PLAY_WITH_DEV = 0x15,
	DEV_CARDS,
	YOU_START,
	I_START,
	DICES_ARE = 0x20,
	ROBBER_CARDS,
	CARD_IS,
	ROBBER_MOVE,
	SETTLEMENT,
	ROAD,
	CITY,
	BANK_TRADE,
	OFFER_TRADE,
	PASS,
	DEV_CARD,
	MONOPOLY,
	YEARS_OF_PLENTY,
	ROAD_BUILDING,
	KNIGHT,
	YES = 0x40,
	NO = 0x41,
	I_WON = 0x50,
	PLAY_AGAIN,
	GAME_OVER,
	ERROR = 0xFE,
	QUIT
};

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
	PLENITY_YEAR = 'P'
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
* NetworkPacket
* Clase base para la definicion de los mensajes
* o paquetes de datos del protocolo de comunicacion.
*/
class NetworkPacket {

public:

	/*
	* Constructores y destructores
	*/
	NetworkPacket(PacketHeader header);
	virtual ~NetworkPacket();

	/*
	* getHeader
	* Devuelve el header del paquete de datos.
	*/
	PacketHeader getHeader(void) const;

	/*
	* getDataStream
	* Devuelve los bytes a mandar como paquete de dato
	* En length se almacena el largo del buffer de bytes.
	* Se devuelve el puntero con lo que hay que mandar.
	*/
	virtual unsigned char* getDataStream(unsigned int& length);

protected:
	PacketHeader header;
};