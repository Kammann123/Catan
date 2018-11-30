#include "ButtonView.h"

void ButtonView::
draw(void) 
{

	ALLEGRO_BITMAP* bmap = nullptr;
	MouseUI* pointer = (MouseUI*)model;
	switch (pointer->getStatus())
	{
		case MouseUI::Status::IDLE:
			bmap = idleBitmap;
			break;

		case MouseUI::Status::SELECTED:
		case MouseUI::Status::DRAGGED:
			bmap = selectedBitmap;
			break;

		case MouseUI::Status::FOCUSED:
			bmap = focusedBitmap;
			break;



	}
	al_draw_rotated_bitmap(bmap, al_get_bitmap_width(bmap) / 2, al_get_bitmap_height(bmap) / 2, pointer->xPos(), pointer->yPos(), NO_ROTATION, NO_FLAGS);
}

ButtonView::
ButtonView(ALLEGRO_BITMAP* focused, ALLEGRO_BITMAP* selected, ALLEGRO_BITMAP* idle, WindowUI* interface_, MouseUI* model_) : UIView(interface_, model_)
{
	focusedBitmap = focused;
	selectedBitmap = selected;
	idleBitmap = idle;


}
