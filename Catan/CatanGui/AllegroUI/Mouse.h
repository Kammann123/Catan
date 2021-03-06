#pragma once

#include "MouseController.h"
#include "ImageConfig.h"

/* Mouse - Clase que modeliza el cursor del mouse en una aplicacion cualquiera
* con el afan de permitir definir el estado actual del mismo, realizar interacciones
* o animaciones con el mismo en base a dichos estados, y manejar un control
* mas alto sobre la interaccion del GUI y el Mouse.
*/
class Mouse {
public:
	/* States - Estados del mouse durante la aplicacion
	*/
	enum States : unsigned int {NORMAL, CLICKING, GRABBING};

	/* Mouse - La construccion del Mouse solo requiere tener conocimiento
	* del display al cual pertenece cuando es creado. Pero puede ser
	* configurado posteriormente.
	*/
	Mouse(ALLEGRO_DISPLAY* display = nullptr);
	~Mouse(void);

	/*
	* parse - Parse permite parsear los eventos de allegro
	* y cambiar el estado del mouse dentro de la aplicacion
	* constantemente
	*/
	void parse(ALLEGRO_EVENT* event);

	/*
	* grab - Agarra un elemento de la interfaz virtualmente,
	* lo cual permite restringir que cualquier otro lo haga
	* tambien.
	*/
	void grab(MouseController* element);

	/*
	* drop - Libera el objeto o el elemento que tenia agarrado
	*/
	void drop(void);

	/*
	* isGrabbing - Permite saber si el mouse dentro de la aplicacion
	* esta actualmente agarrando algo.
	*/
	bool isGrabbing(void);

	/*
	* set - Permite configurar las imagenes para los estados corresspondientes
	* del mouse. En base a lo cual se definen los sprites del cursor.
	* Nota: En la sobrecarga sin identificacion por state, mas bien por id,
	* se permiten agregar estados del cursor especiales, que deben ser forzados
	* exteriormente.
	*/
	void set(States state, const char* filename);
	void set(unsigned int id, const char* filename);

	/*
	* force y release - Permiten forzar un estado especial del cursor
	* o bien liberarlo del mismo.
	*/
	void force(unsigned int id);
	void release(void);

	/*
	* setDisplay - Permite guardar el display a quien pertenece el mouue
	*/
	void setDisplay(ALLEGRO_DISPLAY* display);

	/*
	* update - Actualiza el sprite actual del cursos.
	*/
	void update(void);

	/*
	* privilege - Privilegia a quien fue agarrado para
	* entregarle los eventos
	*/
	void privilege(ALLEGRO_EVENT* event);

	/*
	* isMouse - Devuelve si el evento fue de mouse
	*/
	bool isMouse(ALLEGRO_EVENT* event);

	/* 
	* who - Devuelve el controller que tiene agarrado
	*/
	MouseController* who(void);

private:
	map<States, ALLEGRO_MOUSE_CURSOR*> cursors;
	map<unsigned int, ALLEGRO_MOUSE_CURSOR*> especialCursors;
	ALLEGRO_DISPLAY * display;
	MouseController * clicked;
	ImageConfig images;
	States state;
	bool especialMode;
};