#include "Mouse.h"

Mouse::
Mouse(ALLEGRO_DISPLAY* display) {
	this->display = display;
	this->clicked = nullptr;
	this->images.clear();
	this->state = States::NORMAL;
	this->cursors.clear();
	this->especialMode = false;
}

Mouse::
~Mouse(void) {
	for (auto cursor : cursors) {
		if (cursor.second) {
			al_destroy_mouse_cursor(cursor.second);
		}
	}
}

void
Mouse::parse(ALLEGRO_EVENT* event) {
	/* Almaceno temporalmente el estado actual
	* en el que se encuentra el mouse
	*/
	States prevState = state;

	switch (state) {
		case States::NORMAL:
			if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				state = States::CLICKING;
			}
			break;
		case States::CLICKING:
			if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				state = States::NORMAL;
			}
			else if (event->type == ALLEGRO_EVENT_MOUSE_AXES) {
				state = States::GRABBING;
			}
			break;
		case States::GRABBING:
			if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				state = States::NORMAL;
			}
			else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				state = States::CLICKING;
			}
			break;
	}
}

void
Mouse::grab(MouseController* element) {
	/* En caso de que no se haya guardado correctamente el estado, lo fuerzo
	* a cambiar */
	if (state != States::GRABBING) {
		state = States::GRABBING;
		update();
	}

	/* Guardo el puntero del MouseController
	* que se encuentra actualmente agarrado
	*/
	this->clicked = element;
}

void
Mouse::drop(void) {
	/* En caso de no haber cambiado aun de estado fuerzo al cambio
	* y actualizo es sprite del cursor actual
	*/
	if (state != States::NORMAL) {
		state = States::NORMAL;
		update();
	}

	/* Limpio el controller */
	this->clicked = nullptr;
}

bool
Mouse::isGrabbing(void) {
	return this->clicked != nullptr;
}

void
Mouse::set(States state, const char* filename) {
	images.setConfig(state, filename);
}

void
Mouse::set(unsigned int id, const char* filename) {
	images.setConfig(id, filename);
}

void
Mouse::setDisplay(ALLEGRO_DISPLAY* display) {
	this->display = display;
}

void
Mouse::update(void) {

	if (!especialMode) {
		/* Verifico si para el estado actual existe un sprite
		* definido en la galeria de imagenes correspondientes al mouse
		* ademas verifico tener configurado el display.
		*/
		if (images.has(state)) {
			if (display) {

				/* Primero valido la existencia previa de un cursor,
				* y en caso de haberla, se elimina el mismo y se habre nuevo
				*/
				if (cursors.find(state) == cursors.end()) {
					this->cursors.insert(pair<States, ALLEGRO_MOUSE_CURSOR*>(state, al_create_mouse_cursor(images[state].bitmap, 0, 0)));
				}
				al_set_mouse_cursor(display, cursors[state]);
			}
		}
	}
}

void
Mouse::force(unsigned int id) {

	if (!especialMode) {
		/* Verifico si para el estado especial en el cual
		* se esta forzando el id, se tiene un sprite, y para ese
		* existe precargado el mismo como cursor
		*/
		if (images.has(id)) {
			if (display) {
				/* Pongo en modo especial y entonces se
				* bloquean los cambios de estado por interaccion
				*/
				especialMode = true;

				/*
				* Verifico que no existe, pues de no ser asi, lo agrego
				*/
				if (especialCursors.find(id) == especialCursors.end()) {
					this->especialCursors.insert(pair<unsigned int, ALLEGRO_MOUSE_CURSOR*>(id, al_create_mouse_cursor(images[id].bitmap, 0, 0)));
				}
				al_set_mouse_cursor(display, especialCursors[id]);
			}
		}
	}
}

void
Mouse::release(void) {
	if (especialMode) {
		especialMode = false;
		update();
	}
}

void
Mouse::privilege(ALLEGRO_EVENT* event) {
	if (clicked) {
		clicked->parse(event);

		if (((MouseUI*)clicked->getModel())->getStatus() != MouseUI::Status::DRAGGED) {
			drop();
		}
	}
}

bool
Mouse::isMouse(ALLEGRO_EVENT* event){
	return (
		event->type == ALLEGRO_EVENT_MOUSE_AXES ||
		event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ||
		event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ||
		event->type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
		event->type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY ||
		event->type == ALLEGRO_EVENT_MOUSE_WARPED
	);
}

MouseController*
Mouse::who(void) {
	return clicked;
}