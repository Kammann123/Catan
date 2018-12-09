#pragma once
#include "CatanGame.h"
#include "../CatanGui/AllegroUI/AnimationUI.h"

class Dice : public AnimationUI {
public:
	
	/* Modelo de dados para crear una animacion de los mismos
	* y en funcion de ello obtener los valores random para el juego
	*/
	Dice(string id);

	/**********************************************************
	* Interfaz de acceso, lectura y escritura, de los valores
	* del dado, SETTERS y GETTERS
	**********************************************************/
	void setValue(unsigned int value);
	unsigned int getValue(void);
	void random(void* data);

private:
	unsigned int value;
};