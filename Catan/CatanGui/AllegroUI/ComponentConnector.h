#pragma

#include "MouseUI.h"

/*
* ComponentConnector
* 
* En la nueva version de este AllegroUI framework,
* se añade la capacidad de definir components como 
* conjunto de components, tal que la definicion de nuevos elementos
* graficos consiste en la creacion de los elementos, reaprovechandolos
* y reconstruyendo un nuevo elemento, para lo cual
* se hacen uso de los ComponentConnector's, permiten definir de forma
* generica el llamado de metodos dentro de modelos, desde otros modelos
* mucho mas comodo.
*/
template <class T>
class ComponentConnector {
public:
	/*
	* Mode - Se definen los modos de funcionamiento segun los cuales:
	*	+	NO_ARG: Se hace un llamado del callback sin necesidad
	*		de tomar argumentos.
	*	+	FIXED_ARG: Se hace un llamado del callback con un argumento
	*		fijado en la definicion del ComponentConnector
	*	+	ARG: Se hace un llamado del callback con un argumento que
	*		se recibe en el momento del llamado.
	*/
	enum Mode : unsigned int { NO_ARG, FIXED_ARG, ARG };

	/*
	* ComponentConnector - Se lo construye con el modo, el callback
	* y eventualmente la informacion de cada modo.
	*/
	ComponentConnector(Action callback, Mode mode);
	ComponentConnector(Action callback, T fixedArg);

	/*
	* execute - Ejecuta el callback.
	*/
	void execute(void*);
private:
	Action callback;
	Mode mode;
	T fixedArg;
};

/**************************
* Definicion del template *
**************************/
template <class T>
ComponentConnector<T>::ComponentConnector(Action callback, Mode mode) {
	this->callback = callback;
	this->mode = mode;

	if (this->mode == ComponentConnector::Mode::FIXED_ARG) {
		throw exception("ComponentConnector - FixedArgs es un modo que debe recibir el value");
	}
}

template <class T>
ComponentConnector<T>::ComponentConnector(Action callback, T fixedArg) {
	this->callback = callback;
	this->mode = ComponentConnector::Mode::FIXED_ARG;
	this->fixedArg = fixedArg;
}

template <class T>
void ComponentConnector<T>::execute(void* data) {
	switch (this->mode) {
		case Mode::NO_ARG:
			callback();
			break;
		case Mode::FIXED_ARG:
			callback(*((T*)fixedArg));
			break;
		case Mode::ARG:
			callback(*((T*)data));
			break;
	}
}