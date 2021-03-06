#include "TextFieldView.h"

TextFieldView::
TextFieldView(TextUI* model_) : UIView(model_)
{
	colors.setConfig(MouseUI::Status::IDLE, TF_DEFAULT_BACKGROUND_IDLE_COLOR);
	colors.setConfig(MouseUI::Status::DRAGGED, TF_DEFAULT_BACKGROUND_DRAGGED_COLOR);
	colors.setConfig(MouseUI::Status::SELECTED, TF_DEFAULT_BACKGROUND_SELECTED_COLOR);
	colors.setConfig(MouseUI::Status::HOLDING, TF_DEFAULT_BACKGROUND_SELECTED_COLOR);
	colors.setConfig(MouseUI::Status::FOCUSED, TF_DEFAULT_BACKGROUND_FOCUSED_COLOR);
	colors.setConfig(TF_TEXT_COLOR, TF_DEFAULT_TEXT_COLOR);
	fonts.setConfig(TF_FONT, TF_DEFAULT_FONT, TF_DEFAULT_FONT_SIZE);
}

TextFieldView::
~TextFieldView() {}

void TextFieldView::
draw(void)
{
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
			pointer->xPos() + TF_PADDING_X,
			pointer->yPos() + TF_PADDING_Y,
			0,
			pointer->getText().c_str()
		);		
	}
}

void 
TextFieldView::refactor(void) {
	TextUI* text = (TextUI*)model;

	text->setWidth(TF_PADDING_X * 2 + al_get_text_width(fonts[TF_FONT].font, text->getText().c_str()));
	text->setHeight(TF_PADDING_Y * 2 + al_get_font_line_height(fonts[TF_FONT].font));
}