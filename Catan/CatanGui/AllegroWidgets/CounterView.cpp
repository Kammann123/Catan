#include "CounterView.h"

CounterView::
CounterView(CounterUI* model_) : UIView(model_)
{
	colors.setConfig(CLA_TEXT_COLOR, CLA_DEFAULT_TEXT_COLOR);
	fonts.setConfig(CLA_FONT, CLA_DEFAULT_FONT, CLA_DEFAULT_FONT_SIZE);
}

void 
CounterView::draw(void){
	if (model->getVisible())
	{
		CounterUI* pointer = (CounterUI*)model;
		al_draw_text(
			fonts[CLA_FONT].font,
			colors[CLA_TEXT_COLOR].color,
			pointer->xPos() + 38,
			pointer->yPos() + 15,
			ALLEGRO_ALIGN_LEFT,
			to_string(pointer->getValue()).c_str()
		);
	}
}