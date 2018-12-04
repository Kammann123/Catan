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
	* id - Controller id, identificador de controladores
	*/
	enum Id : unsigned int {MOUSE, TEXT, ANIMATION};

	/* 
	* UIController
	* Se lo construye con un puntero al modelo.
	*/
	UIController(UIModel* model, Id id);
	~UIController(void);

	/*
	* Interfaz de control del modelo basico, con el controller
	* de forma tal que con el mismo se pueda modificar los estados de habilitacion
	* y ejecutar un parseo de los eventos de allegro
	*/
	virtual void parse(ALLEGRO_EVENT* event) = 0; 

	/**************************************************
	* Interfaz de acceso de informacion del controller
	**************************************************/
	void setEnable(bool status);
	UIModel* getModel(void);
	bool getEnable(void);
	Id getId(void);

protected:
	UIModel * model;
	bool enable;
	Id id;
};