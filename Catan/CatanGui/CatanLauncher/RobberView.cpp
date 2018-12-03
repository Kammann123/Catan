#include "RobberView.h"
#include "../AllegroWidgets/UIBuilder.h"

RobberView::RobberView(Robber * model_) : UIView(model_)
{
	///* Creo el componente */
	UIComponent* robber = UIBuilder::createButton("robber");

	///* Configuro el robber! */
	VIEW(robber, 0)->getImages().setConfig(MouseUI::Status::IDLE, ROBBER_IDLE_IMG);
	VIEW(robber, 0)->getImages().setConfig(MouseUI::Status::FOCUSED, ROBBER_FOCUSED_IMG);
	VIEW(robber, 0)->getImages().setConfig(MouseUI::Status::SELECTED, ROBBER_SELECTED_IMG);
	VIEW(robber, 0)->getImages().setConfig(MouseUI::Status::DRAGGED, ROBBER_DRAGGED_IMG);
	VIEW(robber, 0)->updateModelValues();

	///* Lo agrego */
	this->attachComponent(robber);
}

RobberView::~RobberView()
{
}

void RobberView::draw(void)
{
	Robber* robber = (Robber*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		/* Busco la imagen del robber */
		if (images.has((int)robber->getStatus())) {
			btMap = images[((int)robber->getStatus())].bitmap;
		}

		/*Dibujo la carta*/
		if (btMap != nullptr)
			al_draw_bitmap(btMap, robber->xPos(), robber->yPos(), 0);
	}
}

void RobberView::updateModelValues(void)
{
}
