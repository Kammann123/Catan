#include "TextBoxView.h"

TextBoxView::
TextBoxView(TextUI* model_) : UIView(model_)
{
	images.setConfig(MouseUI::Status::IDLE, TB_DEFAULT_BACKGROUND_IDLE_BITMAP);
	images.setConfig(MouseUI::Status::DRAGGED, TB_DEFAULT_BACKGROUND_DRAGGED_BITMAP);
	images.setConfig(MouseUI::Status::SELECTED, TB_DEFAULT_BACKGROUND_SELECTED_BITMAP);
	images.setConfig(MouseUI::Status::HOLDING, TB_DEFAULT_BACKGROUND_SELECTED_BITMAP);
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
			pointer->xPos() + TB_PADDING_X,
			pointer->yPos() + TB_PADDING_Y,
			0,
			pointer->getText().c_str()
		);
	}
}

void TextBoxView::
updateModelValues(void) {
	MouseUI* button = (MouseUI*)model;

	button->setHeight(al_get_bitmap_height(images[MouseUI::Status::IDLE].bitmap));
	button->setWidth(al_get_bitmap_width(images[MouseUI::Status::IDLE].bitmap));
}