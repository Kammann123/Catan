#pragma once

#include "NetworkPacket.h"

/*
* DevCardPacket
* Contiene el paquete de datos para informar
* como es el mazo de cartas de desarrollo
*/
class DevCardPacket : public NetworkPacket {
public:

	/*
	* Constructores y desctructores
	*/
	DevCardPacket(void);
	virtual ~DevCardPacket();

	/*
	* setCard
	* Define una carta del mazo.
	* En caso de pasarse en cantidad
	* devuelve False, en caso de estar bien,
	* devuelve True.
	*/
	bool setCard(DevCardId card, unsigned char indexCard);

	/*
	* getCard
	* Devuelve una carta de desarrollo del mazo.
	* En caso de no estar entre los posibles valores dentro del mazo,
	* devuelve False, en caso de estar bien, devuelve True y guarda la carta en
	* la referencia dada.
	*/
	bool getCard(DevCardId& card, unsigned char indexCard);
	/*
	* getDataStream
	* Arma el paquete de datos a mandar
	*/
	virtual unsigned char* getDataStream(unsigned int& length);

private:
	DevCardId cards[25];
};