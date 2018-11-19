#pragma once

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

protected:
	PacketHeader header;
};