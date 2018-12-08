#include "WindowUI.h"

#include "ChildWindowUI.h"


#define ICON_IMAGE	"CatanGui\\GUIDesigns\\icon.png"
/* Configuraciones e inicializacion estaticas de la clase WindowUI
*  configurar correctamente la inicializacion de allegro
*/
bool WindowUI::allegroWasInit = false;

bool
WindowUI::isAllegroInit(void) {
	return allegroWasInit;
}

void
WindowUI::InitAllegro(void) {

	if( !allegroWasInit ){

		/* Inicializo allegro en general */
		if (!al_init()) {
			return;
		}

		/* Inicializo los addons */
		if (!al_init_primitives_addon()) {
			return;
		}
		if (!al_init_font_addon()) {
			return;
		}
		if (!al_init_ttf_addon()) {
			return;
		}
		if (!al_init_image_addon()) {
			return;
		}
		if (!al_install_audio()) {
			return;
		}
		if (!al_init_acodec_addon()) {
			return;
		}
		if (!al_reserve_samples(5)) {
			return;
		}

		/* Instalo perifericos */
		if (!al_install_keyboard()) {
			return;
		}
		if (!al_install_mouse()) {
			return;
		}

		allegroWasInit = true;
	}
}

void 
WindowUI::CloseAllegro(void) {

}

WindowUI::
WindowUI(string id, size_t width, size_t height, double fps ) {
	this->id = id;
	this->width = width;
	this->height = height;
	this->fps = fps;
	this->display = nullptr;
	this->queue = nullptr;
	this->started = false;
	this->components.clear();
	colors.clear();
	images.clear();
}

WindowUI::
~WindowUI(void) {

	/*
	* Destruyo el display, la cola de eventos	
	* y luego los componentes 
	*/
	_destroy_display();
	_destroy_queue();
	_destroy_timer();
	_destroy_components();
	_destroy_childs();
}

void
WindowUI::_init_display(void) {
	if (display == nullptr) {
		this->display = al_create_display(this->width, this->height);
		mouse.setDisplay(this->display);
		al_set_display_icon(display, al_load_bitmap(ICON_IMAGE));
		al_set_window_title(display, "Fondue Catan");
	}
}

void
WindowUI::_init_queue(void) {
	if (queue == nullptr) {
		this->queue = al_create_event_queue();
	}
}

void
WindowUI::_init_sources(void) {
	if (display && queue) {
		al_register_event_source(queue, al_get_display_event_source(display));
		al_register_event_source(queue, al_get_mouse_event_source());
		al_register_event_source(queue, al_get_keyboard_event_source());
		al_register_event_source(queue, al_get_timer_event_source(timer));
	}
}

void
WindowUI::_init_timer(void) {
	if (timer == nullptr) {
		this->timer = al_create_timer(fps);
	}
}

void 
WindowUI::_destroy_display(void) {
	if (display) {
		al_destroy_display(display);
	}
	mouse.setDisplay(nullptr);
}

void
WindowUI::_destroy_queue(void) {
	if (queue) {
		al_destroy_event_queue(queue);
	}
}

void
WindowUI::_destroy_timer(void) {
	if (timer) {
		al_destroy_timer(timer);
	}
}

void
WindowUI::_destroy_components(void) {
	for (UIComponent* component : components) {
		delete component;
	}
}

void
WindowUI::_destroy_childs(void) {
	for (ChildWindowUI* child : childs) {
		if (child) {
			delete child;
		}
	}
}

string
WindowUI::getId(void) {
	return id;
}

ChildWindowUI*
WindowUI::child(string id) {
	for (ChildWindowUI* child : childs) {
		if (child->getId() == id) {
			return child;
		}
	}
	return nullptr;
}

void
WindowUI::process(void) {}

void
WindowUI::refresh(void) {
	this->draw();
}

void
WindowUI::draw(void) {

	if (started) {

		/* Defino el target del backbuffer */
		al_set_target_backbuffer(display);

		/* Limpio la pantalla con su fondo */
		if (colors.has(WINDOW_BACKGROUND)) {
			al_clear_to_color(colors[WINDOW_BACKGROUND].color);
		}
		if (images.has(WINDOW_BACKGROUND)) {
			al_draw_bitmap(images[WINDOW_BACKGROUND].bitmap, 0, 0, 0);
		}

		/* Redibujo los componentes */
		for (UIComponent* component : components) {
			component->draw();
		}

		/* Redibujo los childs */
		for (ChildWindowUI* child : childs) {
			if (child) {
				if (child->isEnabled()) {
					child->draw();
				}
			}
		}

		/* Actualizo pantalla */
		al_flip_display();
	}
}

void
WindowUI::start(void) {

	/*
	* Construyo todos los elementos basicos que hacen
	* al funcionamiento de la interfaz grafica
	*/
	_init_display();
	_init_queue();
	_init_timer();
	_init_sources();

	/*
	* Se hace refactorizacion de todos los componentes
	*/
	refactor();
	for (ChildWindowUI* child : childs) {
		if (child) {
			child->refactor();
		}
	}

	/* Inicio el timer */
	al_start_timer(timer);

	/* Actualizo cursor */
	mouse.update();
	
	/* Inicio la musica */
	if (sounds.has(WINDOW_MUSIC)) {
		al_play_sample(sounds[WINDOW_MUSIC].sample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &music);
		musicPlaying = true;
	}

	/* Inicio el dibujo */
	started = true;
	draw();
}

void
WindowUI::refactor(void) {
	for (UIComponent* component : components) {
		component->refactor();
	}
}

void
WindowUI::stop(void) {
	/* Paro el sonido */
	if (musicPlaying) {
		al_stop_sample(&music);
		musicPlaying = false;
	}

	/* Paro el timer y el dibujo */
	if (timer) {
		al_stop_timer(timer);
	}
	started = false;
}

void
WindowUI::run(void) {

	/*
	* Busco en la cola de eventos si existen nuevos,
	* en caso de haberlos, los reparto en la interfaz grafica...
	* sus controllers
	*/
	if (al_get_next_event(queue, &event)) {

		/* Verifico el cierre de la ventana
		*/
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			this->stop();
			this->close(&event);
		}
		else {

			/* Primero verifico si tengo alguna ventana hija, y dentro de esas
			* me fijo cual esta activada, en dicho caso, se le pasa el evento a ella
			*/
			for (ChildWindowUI* child : childs) {
				if (child->isEnabled()) {
					child->run(&event);
					return;
				}
			}

			if (mouse.isMouse(&event)) {
				mouse.parse(&event);

				if (mouse.isGrabbing()) {
					mouse.privilege(&event);
				}
				else {
					for (UIComponent* component : components) {
						component->parse(&event);

						MouseController* controller = (MouseController*)(*component)[UIController::Id::MOUSE];
						if (controller) {
							if (MODEL(controller, MouseUI*)->getStatus() == MouseUI::Status::DRAGGED) {
								mouse.grab(controller);
								break;
							}
						}
					}
				}
			}
			else {
				for (UIComponent* component : components) {
					component->parse(&event);
				}
			}
		}
	}

	/*
	* Luego doy tiempo de ejecucion a los diferentes
	* procesos configurables
	*/
	process();
}

void
WindowUI::attachChild(ChildWindowUI* child) {
	child->setParent(this);
	childs.push_back(child);
}

void
WindowUI::detachChild(ChildWindowUI* child) {
	childs.remove(child);
}

void
WindowUI::attachComponent(UIComponent* component) {
	/* Configuro la pertenencia de todos los views
	* del componente a esta ventana en particular.
	*/
	for (UIView* view : component->getView()) {
		view->setWindow(this);
	}

	/* Agrego el componente a la lista de componentes */
	components.push_back(component);

	/* Ejecuto recursivamente el attachment
	* de los subcomponentes del component */
	for (UIComponent* subcomponent : (*component)) {
		attachComponent(subcomponent);
	}
}

void
WindowUI::detachComponent(UIComponent* component) {
	/* Remuevo las Views del componente especifico
	* desconfigurando la window a la que pertenencen
	*/
	for (UIView* view : component->getView()) {
		view->clearWindow();
	}
	
	/* Remuevo al componente de mi lista de componentes */
	components.remove(component);

	/* Ejecuto recursivamente el detachment
	* de los subcomponentes del component */
	for (UIComponent* subcomponent : (*component)) {
		detachComponent(subcomponent);
	}
}

void
WindowUI::enableComponent(string id, bool value) {
	for (UIComponent* component : components) {
		if (component->getId() == id) {
			component->getModel()->setEnable(value);
		}
	}
}

void
WindowUI::visibleComponent(string id, bool value) {
	for (UIComponent* component : components) {
		if (component->getId() == id) {
			component->getModel()->setVisible(value);
		}
	}
}

UIComponent*
WindowUI::operator[](string id) {
	for (UIComponent* component : components) {
		if (component->getId() == id) {
			return component;
		}
	}
	return nullptr;
}

list<UIComponent*>
WindowUI::operator()(string id) {
	list<UIComponent*> seek;
	for (UIComponent* component : components) {
		if (component->getId() == id) {
			seek.push_back(component);
		}
	}
	return seek;
}

bool
WindowUI::isOpen(void) {
	return display != nullptr && started;
}

size_t 
WindowUI::getHeight(void) {
	return height;
}

size_t
WindowUI::getWidth(void) {
	return width;
}

double
WindowUI::getFps(void) {
	return fps;
}

void
WindowUI::setBackground(unsigned char red, unsigned char green, unsigned char blue) {
	colors.setConfig(WINDOW_BACKGROUND, red, green, blue);
}

void
WindowUI::setBackground(const char* image) {
	images.setConfig(WINDOW_BACKGROUND, image);
}

void 
WindowUI::setMusic(const char* image) {
	sounds.setConfig(WINDOW_MUSIC, image);
}

void
WindowUI::setCloseAction(Action close) {
	onClose = close;
}

void
WindowUI::close(void* data) {
	if (onClose) onClose(data);
}

void
WindowUI::shutdown(void) {

	/*
	* Detengo la ejecucion de todos
	* los elementos de la interfaz
	*/
	stop();

	/*
	* Destruyo el display, la cola de eventos
	* y luego los componentes
	*/
	_destroy_display();
	_destroy_queue();
	_destroy_timer();

	started = false;
}

void 
WindowUI::setCursor(const char* image) {
	mouse.set(Mouse::States::NORMAL, image);
}

void
WindowUI::setClickCursor(const char* image) {
	mouse.set(Mouse::States::CLICKING, image);
}

void 
WindowUI::setGrabCursor(const char* image) {
	mouse.set(Mouse::States::GRABBING, image);
}