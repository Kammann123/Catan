#pragma once

#include "CatanData.h"

/*
* DicesData
* Implementacion de CatanData para la informacion
* de los dados tirados por un jugador durante el juego.
*/
class DicesData : public CatanData {

public:

	/* Constructor */
	DicesData(unsigned char fDice, unsigned char sDice);
	DicesData();

	/* 
	* Setters de los campos de dados
	*/
	bool setFirstDice(unsigned char dice);
	bool setSecondDice(unsigned char dice);

	/*
	* Getters que devuelven la 
	* informacion de los dados
	*/
	unsigned char getDices(void) const;
	unsigned char getFirstDice(void) const;
	unsigned char getSecondDice(void) const;

private:
	unsigned char firstDice;
	unsigned char secondDice;
};