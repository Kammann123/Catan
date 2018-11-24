#pragma once

#include <functional>
#include <string>

using namespace std;

/*
* ConditionalCallback - Devuelve un condicional True/False en funcion
* de algun dato externo. Permite saber si ejecuta uno u otro tag.
*/
using ConditionalCallback = function<bool(void)>;

/*
* ProtocolTag
* Se define como un selector de tag dentro del protocolo para continuar
* el flujo del mismo, donde puede funcionar en diversos modos, consistiendo
* en si se define a partir de un string, o con un callback de decision.
*/
class ProtocolTag {
public:

	/* Constructores y destructores */
	ProtocolTag(void) {}
	virtual ~ProtocolTag(void) {}

	/*
	* getTag
	* Devuelve el tag correspondiente que se configuro
	*/
	virtual string getTag(void) = 0;
};