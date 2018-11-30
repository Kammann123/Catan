#include "TextController.h"

TextController::
TextController(TextUI* textUI) : UIController(textUI) {}

TextController::
~TextController(void) {}

void
TextController::parse(ALLEGRO_EVENT* event) {

	/*
	* Busco el modelo, verifico su estado de actividad
	* y luego parseo los eventos correspondientes
	*/
	TextUI* text = (TextUI*)model;

	if (text->getEnable()) {
		if (event->type == ALLEGRO_EVENT_KEY_CHAR) {
			if (!event->keyboard.repeat) {
				if (text->getStatus() == MouseUI::SELECTED) {
					switch (event->keyboard.keycode) {
						case ALLEGRO_KEY_ENTER:
							text->enter(event);
							break;
						case ALLEGRO_KEY_BACKSPACE:
							text->remove();
							break;
						default:
							text->append(event->keyboard.unichar);
							break;
					}
				}
			}
		}
	}
}