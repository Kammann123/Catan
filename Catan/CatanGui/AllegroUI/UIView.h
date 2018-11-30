#pragma once

#include "../../MVC/Observer.h"

#include "UIModel.h"

class WindowUI;

/*
* UIView
* Modeliza la representacion grafica de un modelo en MVC
*/
class UIView : public Observer
{
public:

	/*
	* UIView
	* Se construye con un puntero a la interfaz a la cual pertence
	* para ejecutar una actualizacion de la misma durante los cambios
	* del modelo que se van detectando.
	*/
	UIView(WindowUI* interface_, UIModel* model_);
	~UIView();

	/*
	* update()
	* Implementacion especifica del update para
	* redibujar la interfaz grafica
	*/
	virtual void update(void);

	/*
	* draw()
	* Método que dibuja el objeto en pantalla
	*/
	virtual void draw(void) = 0;

protected:

	WindowUI* interface;
	UIModel* model;
};
