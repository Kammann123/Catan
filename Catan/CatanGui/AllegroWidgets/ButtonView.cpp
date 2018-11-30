#include "ButtonView.h"

void ButtonView::
draw(void) 
{


	if(model->getVisible())
	{
		MouseUI* pointer = (MouseUI*)model;
		al_draw_rotated_bitmap(images[pointer->getStatus()].bitmap, 
								al_get_bitmap_width(images[pointer->getStatus()].bitmap) / 2,
								al_get_bitmap_height(images[pointer->getStatus()].bitmap) / 2,
								pointer->xPos(), 
								pointer->yPos(),
								NO_ROTATION, 
								NO_FLAGS
								);
	}
	
}

ButtonView::
ButtonView(MouseUI* model_) : UIView(model_)
{
	images.setConfig(MouseUI::Status::IDLE, DEFAULT_IDLE_BITMAP);
	images.setConfig(MouseUI::Status::SELECTED, DEFAULT_SELECTED_BITMAP);
	images.setConfig(MouseUI::Status::FOCUSED, DEFAULT_FOCUSED_BITMAP);
	images.setConfig(MouseUI::Status::DRAGGED, DEFAULT_DRAGGED_BITMAP);


}
