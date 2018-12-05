#include "LabelView.h"

LabelView::
LabelView(TextUI* model_) : UIView(model_)
{
	colors.setConfig(LA_TEXT_COLOR, LA_DEFAULT_TEXT_COLOR);
	fonts.setConfig(LA_FONT, LA_DEFAULT_FONT, LA_DEFAULT_FONT_SIZE);
}

void LabelView::
draw(void)
{
	if (model->getVisible())
	{
		TextUI* pointer = (TextUI*)model;
		al_draw_text(
					fonts[LA_FONT].font,
					colors[LA_TEXT_COLOR].color,
					pointer->xPos(),
					pointer->yPos(),
					ALLEGRO_ALIGN_LEFT,
					pointer->getText().c_str()
					);
	}
}