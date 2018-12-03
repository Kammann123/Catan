#include "BuildingView.h"
#include <allegro5/allegro.h>

BuildingView::BuildingView(Building * model_)
{
	images.clear();
	images.setConfig((int)BuildingType::ROAD, ROAD_IMAGE);
	images.setConfig((int)BuildingType::SETTLEMENT, SETTLEMENT_IMAGE);
	images.setConfig((int)BuildingType::CITY, CITY_IMAGE);
}

BuildingView::~BuildingView()
{
}

void BuildingView::draw(void)
{
	Building* building = (Building*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		/* Busco el la imagen de la carta */

		if (images.has((int)building->getType())) {
			btMap = images[(int)building->getType()].bitmap;
		}
		/*Dibujo la carta*/
		if (btMap != nullptr)
			al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap)/2, al_get_bitmap_height(btMap) / 2, building->xPos(), building->yPos(), building->getAngle(), 0);
	}
}

void BuildingView::updateModelValues(void)
{
}
