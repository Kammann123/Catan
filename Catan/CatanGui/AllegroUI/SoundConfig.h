#pragma once

#include "Config.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


/*
* SoundConfig - Almacena configuracion de audio
*/
class SoundConfig : public Config {
public:
	/*
	* SoundConfig 
	*/
	SoundConfig(void);
	~SoundConfig();

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
	bool setConfig(unsigned int index, const char * filename);
	bool setConfig(string index, const char * filename);

private:

	/* Rutinas de destruccion y construccion */
	ALLEGRO_SAMPLE * _create_sample(const char* filename);
	void _destroy_sample(ALLEGRO_SAMPLE* sample);
};