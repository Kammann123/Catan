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
* MouseUI
* Modelizacion para estado con el mouse a un FrameUI
* para agregarle funcionalidades de Mouse. Estas implican la interaccion con el
* mismo, y asi mismo un conjunto de acciones que sean ejecutables en funcion de ello.
*/
class MouseUI : public FrameUI {
public:

	/* Status - Definicion de los posibles estados de un MouseUI
	* genericos para cualquier aplicacion, deberian abarcar cualquier estado
	* que un decorador pueda implementar, pues el estado no depende del decorador para
	* existir, pero si para ser alterado.
	*/
	enum Status : unsigned int { IDLE, FOCUSED, SELECTED, DRAGGED, HOLDING };

	/*
	* MouseUI
	* Se construye a partir de FrameUI
	*/
	MouseUI(string id, size_t width, size_t height, bool dragMode = false, bool holdMode = false);
	~MouseUI(void);

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
	bool getEnableDrag(void);

	void setEnableHold(bool holdStatus);
	bool getEnableHold(void);

	void setStatus(Status status);
	Status getStatus(void);

protected:

	/*
	* Estado actual y modos
	*/
	bool enableDragging;
	bool enableHold;
	Status status;

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