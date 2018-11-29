#include "LabelView.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"


LabelView::
LabelView(Label& model_) :model(model_) {}

void LabelView::
update(void)
{
	al_set_target_bitmap(al_get_backbuffer(display));

	al_draw_filled_rectangle(
		model.xPos(),
		model.yPos(),
		model.xPos() + model.getWidth(),
		model.yPos() + model.getHeight(),
		DEFAULT_BACK_COLOR
	);

	al_draw_text(
		DEFAULT_FONT,
		DEFAULT_TEXT_COLOR,
		model.xPos() + model.getWidth() * PERC_MARGIN,
		model.yPos() + model.getHeight() * PERC_MARGIN / 2,
		ALLEGRO_ALIGN_CENTRE,
		model.getText.c_str()
	);
}