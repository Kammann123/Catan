#pragma once

#include "Config.h"

/*
* ImageConfig
* Permite almacenar imagenes de una forma mas comoda
* para acceder y guardar todas juntas
*/
class ImageConfig :public Config {
public:
	/*
	* ImageConfig -
	* Se crea por defecto vacia
	*/
	ImageConfig();
	~ImageConfig();

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
	bool setConfig(unsigned int index, const char* image);
	bool setConfig(string index, const char* image);

private:

	/* Rutinas de destruccion y construccion */
	ALLEGRO_BITMAP * _create_bitmap(const char* image);
	void _destroy_bitmap(ALLEGRO_BITMAP* bitmap);
};