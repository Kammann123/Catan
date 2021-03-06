#pragma once

#include "../../MVC/Observer.h"

#include "TextConfig.h"
#include "ImageConfig.h"
#include "ColorConfig.h"
#include "SoundConfig.h"

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
	UIView(UIModel* model_);
	UIView();
	~UIView();

	/*
	* refactor
	* Metodo que permite segun su implementacion particularizada
	* a cada View, la refactorizacion del modelo y la view en funcion
	* de componentes o elementos segun lo fuere el caso, para garantizar
	* correcciones durante el transcurso
	*/
	virtual void refactor(void);

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
	ColorConfig& getColors(void);
	TextConfig& getFonts(void);
	ImageConfig& getImages(void);
	SoundConfig& getSamples(void);

	/*
	* Configuramos la relacion con una ventana
	* y al modelo
	*/
	void setWindow(WindowUI* interface_);
	void clearWindow(void);
	void setModel(UIModel* model_);

protected:

	WindowUI* interface;
	UIModel* model;

	ColorConfig colors;
	TextConfig fonts;
	ImageConfig images;
	SoundConfig samples;
};
