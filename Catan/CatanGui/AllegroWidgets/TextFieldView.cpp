#include "TextFieldView.h"

TextFieldView::
TextFieldView(TextUI* model_, WindowUI* interface_) : UIView(interface_, model_)
{
	colors.setConfig(MouseUI::Status::IDLE, DEFAULT_BACKGROUND_IDLE_COLOR);
	colors.setConfig(MouseUI::Status::DRAGGED, DEFAULT_BACKGROUND_DRAGGED_COLOR);
	colors.setConfig(MouseUI::Status::SELECTED, DEFAULT_BACKGROUND_SELECTED_COLOR);
	colors.setConfig(MouseUI::Status::FOCUSED, DEFAULT_BACKGROUND_FOCUSED_COLOR);
	colors.setConfig(TEXT_COLOR, DEFAULT_TEXT_COLOR);
	fonts.setConfig(FONT, DEFAULT_FONT, DEFAULT_FONT_SIZE);
}

TextFieldView::
~TextFieldView()
{
}

void TextFieldView::
draw(void)
{
	ALLEGRO_COLOR backColor;
	TextUI* pointer = (TextUI*)model;

	if (pointer->getVisible()) {

	
			al_draw_filled_rectangle(
				pointer->xPos(),
				pointer->yPos(),
				pointer->xPos() + pointer->getWidth(),
				pointer->yPos() + pointer->getHeight(),
				this->colors[pointer->getStatus()].color
			);

			al_draw_text(
				this->fonts[FONT].font,
				this->colors[TEXT_COLOR].color,
				pointer->xPos() + pointer->getWidth() * PERC_MARGIN,
				pointer->yPos() + pointer->getHeight() * PERC_MARGIN / 2,
				ALLEGRO_ALIGN_CENTRE,
				pointer->getText().c_str());

		

		
	}
}