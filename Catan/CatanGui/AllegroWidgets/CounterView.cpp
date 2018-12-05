#include "CounterView.h"

CounterView::
CounterView(CounterUI* model_) : UIView(model_)
{
	colors.setConfig(LA_TEXT_COLOR, LA_DEFAULT_TEXT_COLOR);
	fonts.setConfig(LA_FONT, LA_DEFAULT_FONT, LA_DEFAULT_FONT_SIZE);
}

void 
CounterView::draw(void){
	if (model->getVisible())
	{
		CounterUI* pointer = (CounterUI*)model;
		al_draw_text(
			fonts[LA_FONT].font,
			colors[LA_TEXT_COLOR].color,
			pointer->xPos() + 38,
			pointer->yPos() + 15,
			ALLEGRO_ALIGN_LEFT,
			to_string(pointer->getValue()).c_str()
		);
	}
}