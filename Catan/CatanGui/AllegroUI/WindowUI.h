#pragma once

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_ttf.h"

#include "Mouse.h"
#include "ColorConfig.h"
#include "ImageConfig.h"
#include "SoundConfig.h"

#include "UIComponent.h"

#include <functional>

#define DEFAULT_FPS 1.0/50

#define WINDOW_BACKGROUND	"background" 
#define WINDOW_MUSIC		"music"

#define MODEL(_component, _cast)	((_cast)(_component->getModel()))

using namespace std;
using namespace std::placeholders;

using Action = function<void(void*)>;

class ChildWindowUI;

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

	/******************************
	* Interfaz principal de la UI *
	******************************/
	virtual void process(void);
	virtual void draw(void);
	virtual void run(void);

	/*********************************
	* Interfaz de ejecucion de la UI *
	*********************************/
	void close(void* data);
	void shutdown(void);
	void start(void);
	void stop(void);

	/***********************
	* Interfaz para Childs *
	***********************/
	void attachChild(ChildWindowUI* child);
	void detachChild(ChildWindowUI* child);

	/************************************************
	* Interfaz para edicion de componentes de la UI *
	************************************************/
	void attachComponent(UIComponent* component);
	void detachComponent(UIComponent* component);
	void enableComponent(string id, bool value);
	void visibleComponent(string id, bool value);

	/*************************************
	* Interfaz de acceso a configuracion *
	*************************************/
	list<UIComponent*> operator()(string id);
	UIComponent* operator[](string id);
	size_t getHeight(void);
	size_t getWidth(void);
	double getFps(void);
	bool isOpen(void);

	/*******************************************
	* Interfaz de configuracion de la WindowUI *
	*******************************************/
	void setBackground(unsigned char red, unsigned char green, unsigned char blue);
	void setClickCursor(const char* image);
	void setGrabCursor(const char* image);
	void setBackground(const char* image);
	void setCursor(const char* image);
	void setCloseAction(Action close);
	void setMusic(const char* image);

protected:

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
	void _destroy_childs(void);

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

	Mouse mouse;

	list<UIComponent*> components;
	list<ChildWindowUI*> childs;
};