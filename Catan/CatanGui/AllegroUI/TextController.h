#pragma once

#include "UIController.h"
#include "TextUI.h"

/*
* TextController
* Controlador de un TextUI
*/
class TextController : public UIController {
public:

	/* 
	* TextController
	* Se construye con una referencia/puntero al modelo TextUI
	*/
	TextController(TextUI* textUI);
	~TextController(void);

	/*
	* parse
	* Parseo de los eventos recibidos
	*/
	virtual void parse(ALLEGRO_EVENT* event);
};