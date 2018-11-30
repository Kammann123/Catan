#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#include "ColorConfig.h"
#include "ImageConfig.h"
#include "SoundConfig.h"

#include "UIComponent.h"

#include <functional>

#define DEFAULT_FPS 1.0/50

#define WINDOW_BACKGROUND	"background" 
#define WINDOW_MUSIC		"music"

#define MODEL(_component, _cast)	((_cast)(_component->getModel()))
#define VIEW(_component, _cast) ((_cast)(_component->getView())

using namespace std;
using namespace std::placeholders;

using Action = function<void(void*)>;

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
	* start y stop
	* Ejecuta las acciones necesarias previas al funcionamiento
	* de la gui para garantizar que funcione correctamente, luego
	* permite parar el funcionamiento de la ui
	*/
	void start(void);
	void stop(void);

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

	/*
	* operator[] - Para acceder mas facilmente
	* a los diferentes componentes segun su id.
	*/
	UIComponent* operator[](string id);

	size_t getHeight(void);
	size_t getWidth(void);
	double getFps(void);
	
	/*
	* setBackground
	* Configura los parametros del fondo de ventana
	*/
	void setBackground(unsigned char red, unsigned char green, unsigned char blue);
	void setBackground(const char* image);
	
	/*
	* setMusic
	* Configura los parametros del fondo de ventana
	*/
	void setMusic(const char* image);

	/* Configuracion del callback de cierre de ventana */
	void setCloseAction(Action close);
	void close(void* data);

	/*
	* shutdown - Cierra todo
	*/
	void shutdown(void);

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
	bool started;
	bool musicPlaying;

	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT_QUEUE * queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT event;
	ALLEGRO_SAMPLE_ID music;

	ColorConfig colors;
	ImageConfig images;
	SoundConfig sounds;

	Action onClose;

	list<UIComponent*> components;
};