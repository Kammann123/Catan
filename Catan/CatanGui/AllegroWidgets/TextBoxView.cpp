#include "TextBoxView.h"

TextBoxView::
TextBoxView(TextUI* model_) : UIView(model_)
{
	images.setConfig(MouseUI::Status::IDLE, TB_DEFAULT_BACKGROUND_IDLE_BITMAP);
	images.setConfig(MouseUI::Status::DRAGGED, TB_DEFAULT_BACKGROUND_DRAGGED_BITMAP);
	images.setConfig(MouseUI::Status::SELECTED, TB_DEFAULT_BACKGROUND_SELECTED_BITMAP);
	images.setConfig(MouseUI::Status::FOCUSED, TB_DEFAULT_BACKGROUND_FOCUSED_BITMAP);
	colors.setConfig(TB_TEXT_COLOR, TB_DEFAULT_TEXT_COLOR);
	fonts.setConfig(TB_FONT, TB_DEFAULT_FONT, TB_DEFAULT_FONT_SIZE);
}

TextBoxView::
~TextBoxView() {}

void TextBoxView::
draw(void)
{
	TextUI* pointer = (TextUI*)model;

	if (pointer->getVisible()) {
		al_draw_bitmap(this->images[pointer->getStatus()].bitmap, pointer->xPos(), pointer->yPos(), 0);

		al_draw_text(
			this->fonts[TB_FONT].font,
			this->colors[TB_TEXT_COLOR].color,
			pointer->xPos() + pointer->getWidth() * TB_PERC_MARGIN,
			pointer->yPos() + pointer->getHeight() * TB_PERC_MARGIN / 2,
			ALLEGRO_ALIGN_CENTRE,
			pointer->getText().c_str()
		);
	}
}