#include "ButtonView.h"

void ButtonView::
draw(void) 
{


	if(model->getVisible())
	{
		MouseUI* pointer = (MouseUI*)model;
		al_draw_bitmap(
			images[pointer->getStatus()].bitmap,
			pointer->xPos(),
			pointer->yPos(),
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
