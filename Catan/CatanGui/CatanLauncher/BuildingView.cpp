#include "BuildingView.h"
#include <allegro5/allegro.h>


#define ROAD_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road.png"
#define SETTLEMENT_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement.png"
#define CITY_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city.png"

BuildingView::BuildingView(Building * model_) : UIView(model_)
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
		/* Busco la imagen del Bulding */

		if (images.has((int)building->getType())) {
			btMap = images[(int)building->getType()].bitmap;
		}
		/*Dibujo la imagen*/
		if (btMap != nullptr)
			al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap)/2, al_get_bitmap_height(btMap) / 2, building->xPos(), building->yPos(), building->getAngle(), 0);
	}
}

void BuildingView::updateModelValues(void)
{
}
