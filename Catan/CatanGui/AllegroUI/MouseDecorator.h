#pragma once

#include "FrameUI.h"

#include <functional>

using namespace std;

/*
* Action - Tipo de dato para callbacks ejecutados por el MouseDecorator
*	+ Permite recibir y pasar como parametro un tipo void*
*/
using Action = function<void(void*)>;

/*
* MouseDecorator
* Modelizacion para el Decorator Pattern, de la decoracion de un FrameUI
* para agregarle funcionalidades de Mouse. Estas implican la interaccion con el
* mismo, y asi mismo un conjunto de acciones que sean ejecutables en funcion de ello.
*/
class MouseDecorator {
public:

	/*
	* MouseDecorator
	* Se construye a partir de FrameUI, al cual se le agrega esta capacidad
	* de funcionar como un decorator del mismo. No puede ser construido
	* con un puntero nullptr, con lo cual se levantaran excepciones.
	*/
	MouseDecorator(FrameUI* frame, bool dragMode=false);
	~MouseDecorator(void);

	/*
	* Configuracion del mouse decorator y sus callbacks
	*/
	void setFocusAction(Action focus);
	void setExitACtion(Action exit);
	void setClickAction(Action click);
	void setReleaseAction(Action release);
	void setDragAction(Action drag);
	void setDropAction(Action drop);
	void setMoveAction(Action move);

	/*
	* Llamadas particulares a los callbacks para el controller
	*/
	void focus(void* data);
	void exit(void* data);
	void click(void* data);
	void release(void* data);
	void drag(void* data);
	void drop(void* data);
	void move(void* data);

	/* Habilitacion del modo dragging con el mouse */
	void setEnableDrag(bool dragStatus);

private:

	/*
	* Puntero al FrameUI decorado y estado actual
	* del modo dragging
	*/
	FrameUI* frame;
	bool enableDragging;

	/*
	* Callbacks para las acciones de los estados que cambia el
	* mouse decorator, cada uno de ellos es una ejecucion de las transiciones
	* de estado que se dan en el mismo
 	*/
	Action onFocus;
	Action onExit;
	Action onClick;
	Action onRelease;
	Action onDrag;
	Action onDrop;
	Action onMove;
};