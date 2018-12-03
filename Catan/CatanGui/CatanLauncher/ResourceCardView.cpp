#include "ResourceCardView.h"
#include <allegro5/allegro.h>

ResourceCardView::ResourceCardView(ResourceCard * model_): UIView(model_)
{
	images.clear();
	images.setConfig((int)ResourceId::FOREST, FOREST_CARD_IMAGE);
	images.setConfig((int)ResourceId::HILL, HILL_CARD_IMAGE);
	images.setConfig((int)ResourceId::MOUNTAIN, MOUNTAIN_CARD_IMAGE);
	images.setConfig((int)ResourceId::FIELD, FIELD_CARD_IMAGE);
	images.setConfig((int)ResourceId::PASTURES, PASTURES_CARD_IMAGE);
	images.setConfig(CARD_BACK_ID, CARD_BACK_IMAGE);
}

ResourceCardView::~ResourceCardView()
{
}

void ResourceCardView::draw(void)
{
	ResourceCard* resourceCard = (ResourceCard*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		/* Busco el la imagen de la carta */
		if (resourceCard->getPlayer() != nullptr)
		{
			if (images.has((int)resourceCard->getResourceId())) {
				btMap = images[((int)resourceCard->getResourceId())].bitmap;
			}
		}
		else {
			if(images.has(CARD_BACK_ID))
				btMap = images[CARD_BACK_ID].bitmap;
		}

		/*Dibujo la carta*/
		if(btMap!=nullptr)
			al_draw_bitmap(btMap, resourceCard->xPos(), resourceCard->yPos(), 0);
	}
}

void ResourceCardView::updateModelValues(void)
{
}
