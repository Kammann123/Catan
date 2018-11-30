#pragma once

#include "../../MVC/Observer.h"

#include "TextConfig.h"
#include "ImageConfig.h"
#include "ColorConfig.h"

#include "UIModel.h"

class WindowUI;

/*
* UIView
* Modeliza la representacion grafica de un modelo en MVC
* 
* Consideracion: Todo objeto, o bien clase heredada de UIView
* es una representacion grafica que por tanto tiene elementos para
* realizar el dibujo, como imagenes, colores y fuentes de texto,
* todas se nuclean en este clase y se da acceso a la misma config.
* Las Views, en cierto sentido, podran tomar valores por defecto
* y garantizar acceso desde el UIComponent.
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

	/*
	* Acceso a configuracion de colores, imagenes
	* y demas
	*/
	ColorConfig& setColors(void);
	TextConfig& setFonts(void);
	ImageConfig& setImages(void);

protected:

	WindowUI* interface;
	UIModel* model;

	ColorConfig colors;
	TextConfig fonts;
	ImageConfig images;
};
