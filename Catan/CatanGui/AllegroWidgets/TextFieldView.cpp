#include "TextFieldView.h"

TextFieldView::TextFieldView(ALLEGRO_FONT * font_, ALLEGRO_COLOR textColor_, TextUI * model_, WindowUI* interface_) : UIView(interface_, model_)
{
	font = font_;
	textColor = textColor_;
	
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

		switch (pointer->getStatus())
		{
		case MouseUI::Status::IDLE:
			backgroundColor = IDLE_COLOR;
			break;

		case MouseUI::Status::SELECTED:
		case MouseUI::Status::DRAGGED:
			backgroundColor = SELECTED_COLOR;
			break;

		case MouseUI::Status::FOCUSED:
			backgroundColor = FOCUSED_COLOR;
			break;

		}

		al_draw_filled_rectangle(
			pointer->xPos(),
			pointer->yPos(),
			pointer->xPos() + pointer->getWidth(),
			pointer->yPos() + pointer->getHeight(),
			backgroundColor
		);

		al_draw_text(
			font,
			textColor,
			pointer->xPos() + pointer->getWidth() * PERC_MARGIN,
			pointer->yPos() + pointer->getHeight() * PERC_MARGIN / 2,
			ALLEGRO_ALIGN_CENTRE,
			pointer->getText().c_str());
	}
}