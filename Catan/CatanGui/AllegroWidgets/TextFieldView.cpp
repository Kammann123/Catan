#include "TextFieldView.h"

TextFieldView::
TextFieldView(TextUI* model_) : UIView(model_)
{
	colors.setConfig(MouseUI::Status::IDLE, TF_DEFAULT_BACKGROUND_IDLE_COLOR);
	colors.setConfig(MouseUI::Status::DRAGGED, TF_DEFAULT_BACKGROUND_DRAGGED_COLOR);
	colors.setConfig(MouseUI::Status::SELECTED, TF_DEFAULT_BACKGROUND_SELECTED_COLOR);
	colors.setConfig(MouseUI::Status::FOCUSED, TF_DEFAULT_BACKGROUND_FOCUSED_COLOR);
	colors.setConfig(TF_TEXT_COLOR, TF_DEFAULT_TEXT_COLOR);
	fonts.setConfig(TF_FONT, DEFAULT_FONT, TF_DEFAULT_FONT_SIZE);
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
				this->fonts[TF_FONT].font,
				this->colors[TF_TEXT_COLOR].color,
				pointer->xPos() + pointer->getWidth() * TF_PERC_MARGIN,
				pointer->yPos() + pointer->getHeight() * TF_PERC_MARGIN / 2,
				ALLEGRO_ALIGN_CENTRE,
				pointer->getText().c_str());		
	}
}
