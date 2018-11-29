#include "ButtonView.h"

void ButtonView::
update(void) 
{

	ALLEGRO_BITMAP* bmap = nullptr;

	switch (model.getStatus())
	{
		case FrameUI::Status::IDLE :
			bmap = idleBitmap;
			break;

		case FrameUI::Status::SELECTED:
			bmap = selectedBitmap;
			break;

		case FrameUI::Status::FOCUSED:
			bmap = focusedBitmap;
			break;

		case FrameUI::Status::ANIMATED :
			// que hacemos?
			break;

		case FrameUI::Status::DRAGGED:
			// que hacemos?
			break;

	}
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_rotated_bitmap(bmap, al_get_bitmap_width(bmap) / 2, al_get_bitmap_height(bmap) / 2, model.xPos(), model.yPos(), NO_ROTATION, NO_FLAGS);
}

ButtonView::
ButtonView(ALLEGRO_BITMAP * focused, ALLEGRO_BITMAP * selected, ALLEGRO_BITMAP * idle, ALLEGRO_DISPLAY * display_, FrameUI & model_) :model(model_)
{
	focusedBitmap = focused;
	selectedBitmap = selected;
	idleBitmap = idle;
	display = display_;
}
