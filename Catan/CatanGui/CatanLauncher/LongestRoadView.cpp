#include "LongestRoadView.h"
#include <allegro5/allegro.h>


#define LONGEST_ROAD_IMG		"CatanGui\\GUIDesigns\\GameMenu\\longest_road.png"
#define LONGEST_ROAD_ID			"longest_road"

LongestRoadView::LongestRoadView(LongestRoad * model_) : UIView(model_)
{
	images.clear();
	images.setConfig("longest_road", LONGEST_ROAD_IMG);
}

LongestRoadView::~LongestRoadView()
{
}

void LongestRoadView::draw(void)
{
	LongestRoad* longestRoad = (LongestRoad*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		/* Busco la imagen del LongestRoad */

		if (images.has(LONGEST_ROAD_ID)) {
			btMap = images[LONGEST_ROAD_ID].bitmap;
		}
		/*Dibujo la imagen*/
		if (btMap != nullptr)
			al_draw_bitmap(btMap, longestRoad->xPos(), longestRoad->yPos(),0);
	}
}

void LongestRoadView::updateModelValues(void)
{
}
