#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#include "UIComponent.h"

#define DEFAULT_FPS 1.0/50

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
	* Se construye el objeto con un tamaño para definir el display
	*/
	WindowUI(size_t width, size_t height, double fps = DEFAULT_FPS);
	~WindowUI(void);

	/*
	* draw
	* Actualiza los elementos a dibujar en la pantalla
	*/
	void draw(void);

	/*
	* start
	* Ejecuta las acciones necesarias previas al funcionamiento
	* de la gui para garantizar que funcione correctamente
	*/
	void start(void);

	/*
	* run
	* Ejecuta la actualizacion de las colas de eventos
	* y revisa nuevas apariciones, parseandolo por los controllers
	* de los componentes de la interfaz grafica
	*/
	void run(void);

	/*
	* attachComponent
	* Agrega un componente de interfaz grafica a la ventana
	*/
	void attachComponent(UIComponent* component);

	/*
	* detachComponent
	* Quita un componente de la interfaz grafica
	*/
	void detachComponent(UIComponent* component);

	/*
	* enableComponent
	* Habilita un componente determinado
	*/
	void enableComponent(string id, bool value);

	/* 
	* visibleComponent
	* Habilita la visibilidad del componente
	*/
	void visibleComponent(string id, bool value);

	/*
	* isOpen
	* Devuelve si esta abierta la ventana o no
	*/
	bool isOpen(void);

	size_t getHeight(void);
	size_t getWidth(void);
	double getFps(void);

private:

	/* Rutinas de inicializacion de la ventana */
	void _init_display(void);
	void _init_queue(void);
	void _init_sources(void);
	void _init_timer(void);

	/* Rutinas de destruccion de la ventana */
	void _destroy_display(void);
	void _destroy_queue(void);
	void _destroy_timer(void);
	void _destroy_components(void);

	size_t width;
	size_t height;
	double fps;
	
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT event;
	ALLEGRO_COLOR background;

	list<UIComponent*> components;
};