#pragma once

#include "UIModel.h"

/*
* UIDecorator
* Clase base y generica para definir un decorador.
* Basicamente es otro UIModel que puede decorar a otro UIModel.
*/
class UIDecorator : public UIModel {
public:

	/*
	* UIDecorator
	* Se construye con el UIModel a quien decora.
	*/
	UIDecorator(UIModel* model);
	~UIDecorator(void);

	virtual bool attach(Observer* observer);
	virtual bool detach(Observer* observer);

	/*
	* Acceso e interfaz basica
	*/
	UIModel* getModel(void);
private:
	UIModel* model;
};