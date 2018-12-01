#pragma once

#include "Config.h"

/*
* TextConfig - Configura y almacena fonts
*/
class TextConfig : public Config {
public:

	/*
	* TextConfig - Se crea por defecto con contenido
	*/
	TextConfig();
	~TextConfig();

	/*
	* clear
	* Permite liberar y limpiar los objetos internos
	*/
	virtual void clear(void);

	/*
	* Permite eliminar un elemento especifico
	* remove
	*/
	virtual void remove(string index);
	virtual void remove(unsigned int index);

	/*
	* setConfig
	* Permite configurar elementos
	*/
	bool setConfig(unsigned int index, const char* font, int size);
	bool setConfig(string index, const char* font, int size);

private:
	
	/* Rutinas de creacion y destruccion */
	ALLEGRO_FONT * _create_font(const char* file, int size);
	void _destroy_font(unsigned int index);
	void _destroy_font(string index);
	void _destroy_font(ALLEGRO_FONT* font);
	void _destroy_strings(void);
	void _destroy_ints(void);
};