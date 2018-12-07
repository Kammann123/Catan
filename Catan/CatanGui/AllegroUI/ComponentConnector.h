#pragma

#include <functional>
#include <vector>

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
#define CREATE_CONNECTOR(_method, _object, _type, ...)	ComponentConnector<T>::saveConnector(ComponentConnector<_type>(bind(&_method, _object, _1), __VA_ARGS__))
#define ATTACH_CONNECTOR(_connector, _type)	bind(&ComponentConnector<_type>::execute, _connector, _1)
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
	static ComponentConnector<T>* saveConnector(ComponentConnector<T> connector);

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
	ComponentConnector(std::function<void(T)> callback, Mode mode);
	ComponentConnector(std::function<void(T)> callback, T fixedArg);

	/*
	* execute - Ejecuta el callback.
	*/
	void execute(void*);
private:
	std::function<void(T)> callback;
	Mode mode;
	T fixedArg;

	static vector<ComponentConnector<T>> connectors;
};

template <class T>
vector<ComponentConnector<T>> ComponentConnector<T>::connectors = {};

template <class T>
ComponentConnector<T>* 
ComponentConnector<T>::saveConnector(ComponentConnector<T> connector) {
	ComponentConnector<T>::connectors.push_back(connector);
	return &connector;
}

/**************************
* Definicion del template *
**************************/
template <class T>
ComponentConnector<T>::ComponentConnector(std::function<void(T)> callback, Mode mode) {
	this->callback = callback;
	this->mode = mode;

	if (this->mode == ComponentConnector::Mode::FIXED_ARG) {
		throw exception("ComponentConnector - FixedArgs es un modo que debe recibir el value");
	}
}

template <class T>
ComponentConnector<T>::ComponentConnector(std::function<void(T)> callback, T fixedArg) {
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