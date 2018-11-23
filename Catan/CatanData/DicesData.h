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
	DicesData(unsigned int fDice, unsigned int sDice);
	DicesData();

	/* 
	* Setters de los campos de dados
	*/
	bool setFirstDice(unsigned int dice);
	bool setSecondDice(unsigned int dice);

	/*
	* Getters que devuelven la 
	* informacion de los dados
	*/
	unsigned int getDices(void) const;
	unsigned int getFirstDice(void) const;
	unsigned int getSecondDice(void) const;

private:
	unsigned int firstDice;
	unsigned int secondDice;
};