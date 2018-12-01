#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <map>
#include <string>
#include <exception>

using namespace std;

/*
* config_t - Tipo de dato en el cual convergen los diferentes tipos
* que se pueden almacenar para definir una configuracion visual de los View
*/
typedef union {
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_FONT* font;
	ALLEGRO_COLOR color;
	ALLEGRO_SAMPLE *sample;
} config_t;

/*
* Config
* Clase que permite almacenar y organizar diferentes elementos de configuracion
* accediendo mediante tokens representativos que facilitan la programacion
* de la interfaz grafica
*/
class Config {
public:

	/*
	* Config - Se crea por defecot una Config vacia
	*/
	Config(void);
	~Config(void);

	/*
	* operator[]
	* Accede directamente al contenido de los mapas de configuracion.
	* Si no lo encuentra, levanta excepcion.
	*/
	config_t operator[](string index);
	config_t operator[](unsigned int index);

	/*
	* clear
	* Permite liberar todos los objetos actuales
	*/
	virtual void clear(void) = 0;

	/*
	* remove
	* Permite eliminar un elemento especifico
	*/
	virtual void remove(string index) = 0;
	virtual void remove(unsigned int index) = 0;

	/*
	* has
	* Devuelve si tiene elementos
	*/
	bool has(void);
	bool has(unsigned int index);
	bool has(string index);

protected:

	/*
	* Diferentes accesos a la config, dos maneras, mediante
	* una referencia numerica o bien una referencia textual
	*/
	map<unsigned int, config_t>	intConfig;
	map<string, config_t> stringConfig;
};