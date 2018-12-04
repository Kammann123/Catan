#pragma once
#include "CatanGame.h"
#include "../CatanGui/AllegroUI/AnimationUI.h"

class Dice : public AnimationUI {
public:

	/*
	* Dice - Se construye inicialmente
	* sin mas informacion que una referencia al juego
	*/
	Dice(int64_t maxTimerCount, Mode mode_, string id, size_t width, size_t height, bool dragMode = false, bool holdMode = false, int timesToLoop = 0);

	//setter
	void setValue(unsigned int value);

	//getter
	unsigned int getValue(void);
private:
	unsigned int value;
};