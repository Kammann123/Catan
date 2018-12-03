#pragma once

#include "UIController.h"
#include "AnimationUI.h"

/*
* AnimationController
* Controlador de un AnimationUI
*/
class AnimationController : public UIController {
public:

	/*
	* AnimationController
	* Se construye con una referencia/puntero al modelo AnimationUI
	*/
	AnimationController(AnimationUI* animationUI);
	~AnimationController(void);

	/*
	* parse
	* Parseo de los eventos recibidos
	*/
	virtual void parse(ALLEGRO_EVENT* event);
};