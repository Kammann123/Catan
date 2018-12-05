#include "ChildWindowUI.h"

void 
ChildWindowUI::_create_bitmap(void) {
	if (bitmap != nullptr) {
		bitmap = al_create_bitmap(width, height);
	}
}

void
ChildWindowUI::_destroy_bitmap(void) {
	if (bitmap) {
		al_destroy_bitmap(bitmap);
	}
}

ChildWindowUI::
ChildWindowUI(size_t _width, size_t _height) : WindowUI(_width, _height) {
	this->width = width;
	this->height = height;
	this->enable = false;

	_create_bitmap();
}

ChildWindowUI::
~ChildWindowUI(void) {
	_destroy_bitmap();
}

void
ChildWindowUI::setParent(WindowUI* parent) {
	this->parent = parent;
}

void
ChildWindowUI::run(ALLEGRO_EVENT* event) {

	/* Primero verifico si tengo alguna ventana hija, y dentro de esas
	* me fijo cual esta activada, en dicho caso, se le pasa el evento a ella
	*/
	for (ChildWindowUI* child : childs) {
		if (child->isEnabled()) {
			child->run(event);
			return;
		}
	}

	/* En caso de no tener ventanas hijas activadas... se comunica el evento
	* a los controllers de los componentes de la interfaz grafica.
	* Detalle, en esta version, no considero factible el reconocimiento del mouse
	* como objeto para controlar cantidad de drag objects
	*/
	for (UIComponent* component : components) {
		if (component) {
			component->parse(event);
		}
	}

	/*
	* Luego se ejecuta la rutina de procesamiento 
	*/
	process();
}

void
ChildWindowUI::setEnable(bool status) {
	this->enable = status;
}

void 
ChildWindowUI::process(void) {}

bool
ChildWindowUI::isEnabled(void) {
	return enable;
}

void
ChildWindowUI::draw(void) {

	/* Primer para dibujar, verifico que no tenga alguna ventana hija
	* que ademas, este activa, en cuyo cayo, primero dibujo lo mio, y luego
	* le paso el control a ella. Para este paso, se define un 
	* bitmap buffer, en el cual se dibuja para posicion la ventana correctamente.
	*/
	ALLEGRO_DISPLAY* display = al_get_current_display();
	al_set_target_bitmap(bitmap);
	
	/* Limpio pantalla con los fondos */
	if (colors.has(CHILD_WINDOW_BACKGROUND)) {
		al_clear_to_color(colors[CHILD_WINDOW_BACKGROUND].color);
	}
	if (images.has(CHILD_WINDOW_BACKGROUND)) {
		al_draw_bitmap(images[CHILD_WINDOW_BACKGROUND].bitmap, 0, 0, 0);
	}

	/* Redibujo components */
	for (UIComponent* component : components) {
		if (component) {
			component->draw();
		}
	}

	/* Redibujo los childs */
	for (ChildWindowUI* child : childs) {
		if (child) {
			if (child->isEnabled()) {
				child->draw();
			}
		}
	}

	/*
	* Vuelvo a configurar el target display y luego dibujo donde corresponde
	* el bitmap de la ventana del ChildWindow
	*/
	al_set_target_backbuffer(display);
	al_draw_bitmap(bitmap, x, y, 0);
}

void
ChildWindowUI::setPosition(pos_t x, pos_t y) {
	this->x = x;
	this->y = y;
}

size_t
ChildWindowUI::getHeight(void) {
	return height;
}

size_t
ChildWindowUI::getWidth(void) {
	return width;
}