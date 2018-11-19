#pragma once

#include "NetworkPacket.h"

/*
* DicesPacket
* Define el paquete de datos con la informacion para determinar
* el valor de dados que tiro el otro usuario.
*/
class DicesPacket : public NetworkPacket {

public:

	enum class Dices : unsigned int {FIRST, SECOND};

	/*
	* Constructores y destructores
	*/
	DicesPacket(void);
	virtual ~DicesPacket();

	/*
	* Setters y Getters de los dados
	*/
	bool setFirstDice(unsigned char dice);
	bool setSecondDice(unsigned char dice);
	unsigned char getFirstDice(void);
	unsigned char getSecondDice(void);

private:

	bool _set_dice(unsigned char dice, Dices diceIndex);

	unsigned char dices[2];
};