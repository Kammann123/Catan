#pragma once

#include "UIModel.h"

/*
* Declaracion de tipos genericos usados en FrameUI, garantizan
* futuras actualizaciones y compatibilidad.
*/
using pos_t = double;
using size_t = unsigned int;

/*
* FrameUI
* Clase FrameUI, modelizacion de un elemento o componente grafico rectangular,
* sobre el cual se pueden correr diferentes acciones e interacciones, representado
* por sus relaciones de tamaño y ubicaciones.
* La funcion general es a partir de este elemento agregar decoradores que permitan
* sumar funcionalidades, donde lo que se agregar son decoradores o modelos con nuevas
* funcionalidades, y sus respectivos controladores.
*/
class FrameUI : public UIModel {

public:
	/* Status - Definicion de los posibles estados de un FrameUI
	* genericos para cualquier aplicacion, deberian abarcar cualquier estado 
	* que un decorador pueda implementar, pues el estado no depende del decorador para 
	* existir, pero si para ser alterado.
	*/
	enum Status : unsigned int { IDLE, FOCUSED, SELECTED, DRAGGED, ANIMATED };

	/*
	* FrameUI
	* Se construye con un tamaño, y luego se posible definir,
	* posiciones y estado inicial, de todas formas tiene argumento por defecto
	*/
	FrameUI(size_t width, size_t height, pos_t x = 0, pos_t y = 0, Status status = IDLE);
	~FrameUI(void);

	/*
	* Interfaz para el manejo de los estados, y su lectura.
	*/
	void setPosition(pos_t x, pos_t y);
	void addPosition(pos_t x, pos_t y);
	void setWidth(size_t width);
	void setHeight(size_t height);
	void setStatus(Status status);

	Status getStatus(void);
	size_t getWidth(void);
	size_t getHeight(void);
	pos_t xPos(void);
	pos_t yPos(void);
	
	/*
	* isInside
	* Logica de control para determinar si una coordenada
	* se ubica en su interior
	*/
	bool isInside(pos_t x, pos_t y);

protected:
	pos_t x;
	pos_t y;
	size_t height;
	size_t width;
	Status status;
};