#pragma once

#include <iterator>
#include <exception>
#include <functional>
#include <vector>

using namespace std;
using namespace std::placeholders;
/*************************************************************************
* Macros de utilizacion del ComponentConnector 
*
* Su utilizacion se comprende de dos fases, la 
* creacion del conector mediante el uso de
* CREATE_CONNECTOR:
*	+CREATE_CONNECTOR(
*		TextUI::setText, 
*		label, 
*		string, 
*		ComponentConnector::Mode::NO_ARG
*	)
* Luego se debera agregar el conector como callback
* de alguna rutina de accion.
*	+ myButton->setClickAction( ATTACH_CONNECTOR(myConnector, string) )
*************************************************************************/
#define CREATE_CONNECTOR(_type, ...) ComponentConnector<_type>::createConnector(new ComponentConnector<_type>(__VA_ARGS__))

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

	/**************************************************
	* Interfaz de almacenamiento estatico de 
	* los conectores para no recargar la programacion
	* de la interfaz en su uso
	**************************************************/
	static function<void(void*)> createConnector(ComponentConnector<T>* connector){
		return bind(&ComponentConnector<T>::execute, connector, _1);
	}

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
	ComponentConnector(function<void(T)> callback);
	ComponentConnector(function<void(void)> callback);
	ComponentConnector(function<void(T)> callback, T fixedArg);

	/*
	* execute - Ejecuta el callback.
	*/
	void execute(void*);

private:
	function<void(T)> callback;
	function<void(void)> noArgCallback;
	Mode mode;
	T fixedArg;
};

template <class T>
ComponentConnector<T>::ComponentConnector(function<void(T)> callback) {
	this->callback = callback;
	this->mode = Mode::ARG;
}

template <class T>
ComponentConnector<T>::ComponentConnector(function<void(void)> callback) {
	this->noArgCallback = callback;
	this->mode = Mode::NO_ARG;
}

template <class T>
ComponentConnector<T>::ComponentConnector(function<void(T)> callback, T fixedArg) {
	this->callback = callback;
	this->mode = Mode::FIXED_ARG;
	this->fixedArg = fixedArg;
}

template <class T>
void ComponentConnector<T>::execute(void* data) {
	switch (this->mode) {
		case Mode::NO_ARG:
			noArgCallback();
			break;
		case Mode::FIXED_ARG:
			callback(fixedArg);
			break;
		case Mode::ARG:
			callback(*((T*)data));
			break;
	}
}