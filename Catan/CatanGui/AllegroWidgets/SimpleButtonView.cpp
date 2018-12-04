#include "SimpleButtonView.h"
#include "allegro5/allegro_primitives.h"

SimpleButtonView::
SimpleButtonView() : UIView() {
	images.clear();

	colors.setConfig(SIMPLE_BUTTON_TEXTCOLOR, DEFAULT_SP_TEXTCOLOR);
	fonts.setConfig(SIMPLE_BUTTON_TEXTFONT, DEFAULT_SP_TEXTFONT, DEFAULT_SP_TEXTSIZE);
}

SimpleButtonView::
~SimpleButtonView() {}

void
SimpleButtonView::draw(void) {
	ALLEGRO_COLOR bgColor;
	ALLEGRO_COLOR textColor;
	ALLEGRO_FONT* textFont;

	/*
	* Hago uso de los valores por defecto colorde las configs
	* de colores y fuentes de texto.
	*/
	TextUI* button = (TextUI*)model;

	if (model->getVisible()) {

		/* Busco el color del boton */
		if (colors.has(button->getStatus())) {
			bgColor = colors[button->getStatus()].color;
		}
		else {
			bgColor = al_map_rgb(255, 255, 255);
		}

		/* Busco el color del texto */
		textColor = colors[SIMPLE_BUTTON_TEXTCOLOR].color;

		/* Busco la fuente */
		textFont = fonts[SIMPLE_BUTTON_TEXTFONT].font;

		/* Lo dibujo */
		al_draw_filled_rectangle(
			button->xPos(),
			button->yPos(),
			button->xPos() + button->getWidth(),
			button->yPos() + button->getHeight(),
			bgColor
		);

		al_draw_text(
			textFont,
			textColor,
			button->xPos() + PADDING_X,
			button->yPos() + (button->getHeight() - al_get_font_line_height(textFont)) / 2,
			0,
			button->getText().c_str()
		);
	}
}

void 
SimpleButtonView::updateModelValues(void) {
	TextUI* text = (TextUI*)model;

	text->setWidth(2 * PADDING_X + al_get_text_width(fonts[SIMPLE_BUTTON_TEXTFONT].font, text->getText().c_str()));
}