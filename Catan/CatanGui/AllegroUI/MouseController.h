#pragma once

#include "UIController.h"
#include "MouseUI.h"

/*
* MouseController
* Controller para un MouseUI que recibe los eventos de la interfaz
* grafica por Allegro y luego ejecuta un parseo para definir los estados
* correspondientes en el mismo.
*/
class MouseController : public UIController {
public:

	/*
	* MouseController
	* Se lo construye con una referencia al MouseDecorator adecuado
	*/
	MouseController(MouseUI* frame);
	~MouseController(void);

	/*
	* Definicion del parser de los eventos de allegro
	*/
	virtual void parse(ALLEGRO_EVENT* event);
};