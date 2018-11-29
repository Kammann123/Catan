#pragma once

#include "UIModel.h"

#include "allegro5/allegro.h"

/*
* UIController
* Clase base y generica para el desarrollo de los controllers
* donde la idea esta basicamente en desarrollar controllers que parsean a partir
* de los eventos de allegro, determinando para ellos una aplicacion o funcionalidad
* especifica del controller.
*/
class UIController {
public:

	/* 
	* UIController
	* Se lo construye con un puntero al modelo.
	*/
	UIController(UIModel* model);
	~UIController(void);

	/*
	* Interfaz de control del modelo basico, con el controller
	* de forma tal que con el mismo se pueda modificar los estados de habilitacion
	* y ejecutar un parseo de los eventos de allegro
	*/
	virtual void parse(ALLEGRO_EVENT* event) = 0;
	UIModel* getModel(void);

private:
	UIModel * model;
};