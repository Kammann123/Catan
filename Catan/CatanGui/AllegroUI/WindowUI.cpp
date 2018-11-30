#include "WindowUI.h"

/* Configuraciones e inicializacion estaticas de la clase WindowUI
* para configurar correctamente la inicializacion de allegro
*/
bool WindowUI::allegroWasInit = false;

bool
WindowUI::isAllegroInit(void) {
	return allegroWasInit;
}

void
WindowUI::InitAllegro(void) {

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