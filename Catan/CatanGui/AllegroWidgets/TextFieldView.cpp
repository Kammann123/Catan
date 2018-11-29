#include "TextFieldView.h"


TextFieldView::
TextFieldView(TextField& model_) :model(model_) {}

TextFieldView::
~TextFieldView()
{
}

void TextFieldView::
update(void)
{
	ALLEGRO_COLOR backColor;

	switch (model.getStatus())
	{
	case FrameUI::Status::IDLE:
		backColor = IDLE_BACK_COLOR;
		break;

	case FrameUI::Status::SELECTED:
		backColor = SELECTED_BACK_COLOR;
		break;

	case FrameUI::Status::FOCUSED:
		backColor = FOCUSED_BACK_COLOR;
		break;

	case FrameUI::Status::ANIMATED:
		// que hacemos?
		break;

	case FrameUI::Status::DRAGGED:
		// que hacemos?
		break;

	}
	al_set_target_bitmap(al_get_backbuffer(display));

	al_draw_filled_rectangle(
		model.xPos(),
		model.yPos(),
		model.xPos() + model.getWidth(),
		model.yPos() + model.getHeight(),
		backColor
	);

	al_draw_text(
		DEFAULT_FONT,
		DEFAULT_TEXT_COLOR,
		model.xPos() + model.getWidth() * PERC_MARGIN,
		model.yPos() + model.getHeight() * PERC_MARGIN / 2,
		ALLEGRO_ALIGN_CENTRE,
		model.getText.c_str());
}