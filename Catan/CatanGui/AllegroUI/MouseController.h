#pragma once

#include "UIController.h"
#include "MouseDecorator.h"

/*
* MouseController
* Controller para un MouseDecorator que recibe los eventos de la interfaz
* grafica por Allegro y luego ejecuta un parseo para definir los estados
* correspondientes en el mismo.
*/
class MouseController : public UIController {
public:

	/*
	* MouseController
	* Se lo construye con una referencia al MouseDecorator adecuado
	*/
	MouseController(MouseDecorator* decorator);
	~MouseController(void);

	/*
	* Definicion del parser de los eventos de allegro
	*/
	virtual void parse(ALLEGRO_EVENT* event);
};