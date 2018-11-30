#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

/*
* WindowUI
* Modelizacion de una ventana como interfaz grafica
*/
class WindowUI {

public:

	/* Inicializacion y control de estado estatico del modulo de allegro
	* para la utilizacion de Window UI
	*/
	static bool allegroWasInit;
	static bool isAllegroInit(void);
	static void InitAllegro(void);

	/*
	* WindowUI 
	* Se construye el objeto con un tama�o para definir el display
	*/
	WindowUI(size_t width, size_t height);
	~WindowUI(void);

	/*
	* draw
	* Actualiza los elementos a dibujar en la pantalla
	*/
	void draw(void);

	/*
	* run
	* Ejecuta la actualizacion de las colas de eventos
	* y revisa nuevas apariciones, parseandolo por los controllers
	* de los componentes de la interfaz grafica
	*/
	void run(void);

private:

	/* Rutinas de inicializacion de la ventana */
	void _init_display(void);
	void _init_queue(void);
	void _init_sources(void);

	/* Rutinas de destruccion de la ventana */
	void _destroy_display(void);
	void _destroy_queue(void);

	size_t width;
	size_t height;
	
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_EVENT event;
	ALLEGRO_COLOR background;
};