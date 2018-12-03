#pragma once

#include "../CatanGui/AllegroUI/AnimationUI.h"

class Dice : public AnimationUI {
public:

	/*
	* Dice - Se construye inicialmente
	* sin mas informacion que una referencia al juego
	*/
	Dice(CatanGame* game);

	//setter
	void setValue(unsigned int value);

	//getter
	unsigned int getValue(void);


private:
	unsigned int value;
	CatanGame* game;
};