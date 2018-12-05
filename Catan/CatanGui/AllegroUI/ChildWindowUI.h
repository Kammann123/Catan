#pragma once

#include "WindowUI.h"

#define CHILD_WINDOW_BACKGROUND	"background"

/*
* ChildWindowUI - Clase ventana hijo de WindowUI, no porque herede
* sino porque su aparicion y funcionamiento es gobernado por una WIndowUI
* parent en la cual nace. Esta pensada para pop-ups y sub ventanas internas
* que aparecen mas dinamicamente
*/
class ChildWindowUI : public WindowUI {
public:
	/*
	* ChildWindowUI - Se construye necesariamente con una referencia al padre
	* y las dimensiones de la misma, para poder ser dimensionada correctamente
	* en el dibujo de la misma
	*/
	ChildWindowUI(string id, size_t _width, size_t _height);
	~ChildWindowUI(void);

	/******************************************
	* Interfaz de ejecucion de la ChildWindow *
	******************************************/
	void run(ALLEGRO_EVENT* event);
	void setEnable(bool status);
	virtual void process(void);
	bool isEnabled(void);
	void refresh(void);
	void draw(void);

	/********************************
	Interfaz general de ChildWindow *
	********************************/
	void setPosition(pos_t x, pos_t y);
	void setParent(WindowUI* parent);

	/****************************************
	* Interfaz de acceso a la configuracion *
	****************************************/
	size_t getHeight(void);
	size_t getWidth(void);

private:

	/************************************************
	* Constructores, destructores e inicializadores *
	************************************************/
	void _create_bitmap(void);
	void _destroy_bitmap(void);

	WindowUI * parent;

	ALLEGRO_BITMAP* bitmap;
	
	bool enable;
	pos_t x;
	pos_t y;
};