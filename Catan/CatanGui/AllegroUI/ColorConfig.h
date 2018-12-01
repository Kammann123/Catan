#pragma once

#include "Config.h"

/* Valores defecto de colores */
#define DEFAULT_0	0, 255, 0, 0
#define DEFAULT_1   1, 0, 255, 0
#define DEFAULT_2   2, 0, 0, 255
#define DEFAULT_3   3, 255, 0, 255

/*
* ColorConfig - Almacena configuracion de color
*/
class ColorConfig : public Config {
public:
	/*
	* ColorConfig - Se construye por defecto con valores
	* iniciales
	*/
	ColorConfig(void);
	~ColorConfig();

	/*
	* clear
	* Permite liberar y limpiar los objetos internos
	*/
	virtual void clear(void);

	/*
	* remove
	* Permite eliminar un elemento especifico
	*/
	virtual void remove(string index);
	virtual void remove(unsigned int index);

	/*
	* setConfig
	* Permite configurar elementos
	*/
	bool setConfig(unsigned int index, unsigned char red, unsigned char green, unsigned char blue);
	bool setConfig(string index, unsigned char red, unsigned char green, unsigned char blue);
};