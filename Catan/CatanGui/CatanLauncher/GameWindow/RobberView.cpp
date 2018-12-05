#include "RobberView.h"
#include "../../AllegroWidgets/UIBuilder.h"

#define ROBBER_IDLE_IMG		"CatanGui\\GUIDesigns\\GameMenu\\robber\\idle_robber.png"
#define ROBBER_FOCUSED_IMG	"CatanGui\\GUIDesigns\\GameMenu\\robber\\focused_robber.png"
#define ROBBER_SELECTED_IMG	"CatanGui\\GUIDesigns\\GameMenu\\robber\\selected_robber.png"
#define ROBBER_DRAGGED_IMG	ROBBER_SELECTED_IMG

RobberView::RobberView(Robber * model_) : UIView(model_)
{

	/* Configuro el robber! */
	images.setConfig(MouseUI::Status::IDLE, ROBBER_IDLE_IMG);
	images.setConfig(MouseUI::Status::FOCUSED, ROBBER_FOCUSED_IMG);
	images.setConfig(MouseUI::Status::SELECTED, ROBBER_SELECTED_IMG);
	images.setConfig(MouseUI::Status::DRAGGED, ROBBER_DRAGGED_IMG);
}

void RobberView::draw(void)
{
	Robber* robber = (Robber*)model;
	ALLEGRO_BITMAP * btMap = nullptr;

	if (model->getVisible()) {
		if (images.has((int)robber->getStatus())) {
			btMap = images[((int)robber->getStatus())].bitmap;
		}

		if (btMap != nullptr) {
			al_draw_bitmap(btMap, robber->xPos(), robber->yPos(), 0);
		}
	}
}

void RobberView::refactor(void){
	Robber* robber = (Robber*)model;

	robber->setWidth( al_get_bitmap_width(images[MouseUI::Status::IDLE].bitmap) );
	robber->setHeight( al_get_bitmap_height(images[MouseUI::Status::IDLE].bitmap) );
}
