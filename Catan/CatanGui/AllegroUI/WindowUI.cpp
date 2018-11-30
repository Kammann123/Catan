#include "WindowUI.h"

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

WindowUI::
WindowUI(size_t width, size_t height, double fps) {
	this->width = width;
	this->height = height;
	this->fps = fps;
	this->display = nullptr;
	this->queue = nullptr;
	this->started = false;
	this->components.clear();
	colors.clear();
	images.clear();

	/*
	* Construyo todos los elementos basicos que hacen
	* al funcionamiento de la interfaz grafica
	*/
	_init_display();
	_init_queue();
	_init_timer();
	_init_sources();
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
}

void
WindowUI::_init_display(void) {
	if (display == nullptr) {
		this->display = al_create_display(this->width, this->height);
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
WindowUI::draw(void) {

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

	/* Actualizo pantalla */
	al_flip_display();
}

void
WindowUI::start(void) {
	al_start_timer(timer);
	started = true;
	draw();
}

void
WindowUI::stop(void) {
	al_stop_timer(timer);
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
			for (UIComponent* component : components) {
				component->parse(&event);
			}
		}
	}
}

void
WindowUI::attachComponent(UIComponent* component) {
	component->getView()->setWindow(this);
	components.push_back(component);
}

void
WindowUI::detachComponent(UIComponent* component) {
	component->getView()->clearWindow();
	components.remove(component);
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
WindowUI::setCloseAction(Action close) {
	onClose = close;
}

void
WindowUI::close(void* data) {
	if (onClose) onClose(data);
}