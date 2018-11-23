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
enum PacketHeader : unsigned char {
	OTHER = 0x00,
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