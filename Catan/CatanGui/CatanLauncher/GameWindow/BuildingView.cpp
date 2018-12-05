#include "BuildingView.h"
#include <allegro5/allegro.h>
#include "../../../CatanGame/Player.h"

/**********************
* Imagenes de la View *
**********************/
#define ROAD_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road.png"
#define ROAD_FOCUSED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_focused.png"
#define ROAD_SELECTED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_selected.png"

#define SETTLEMENT_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement.png"
#define SETTLEMENT_FOCUSED_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_focused.png"
#define SETTLEMENT_SELECTED_IMAGE "CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_selected.png"

#define CITY_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city.png"
#define CITY_FOCUSED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_focused.png"
#define CITY_SELECTED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_selected.png"

#define INDEX(_type, _state) string( to_string((int)BuildingType::_type) + "_" + to_string((int)MouseUI::Status::_state) )

BuildingView::BuildingView(Building * model_) : UIView(model_)
{
	images.clear();
	images.setConfig(INDEX(ROAD, IDLE), ROAD_IMAGE);
	images.setConfig(INDEX(ROAD, FOCUSED), ROAD_FOCUSED_IMAGE);
	images.setConfig(INDEX(ROAD, SELECTED), ROAD_SELECTED_IMAGE);
	images.setConfig(INDEX(ROAD, DRAGGED), ROAD_SELECTED_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, IDLE), SETTLEMENT_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, FOCUSED), SETTLEMENT_FOCUSED_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, SELECTED), SETTLEMENT_SELECTED_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, DRAGGED), SETTLEMENT_SELECTED_IMAGE);
	images.setConfig(INDEX(CITY, IDLE), CITY_IMAGE);
	images.setConfig(INDEX(CITY, FOCUSED), CITY_FOCUSED_IMAGE);
	images.setConfig(INDEX(CITY, SELECTED), CITY_SELECTED_IMAGE);
	images.setConfig(INDEX(CITY, DRAGGED), CITY_SELECTED_IMAGE);
}

void BuildingView::draw(void)
{
	Building* building = (Building*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		/* Busco la imagen del Bulding */
		string index = to_string((unsigned int)building->getType()) + "_" + to_string((unsigned int)building->getStatus());

		if (images.has(index) ) {
			btMap = images[index].bitmap;
		}
		/*Dibujo la imagen*/
		if (btMap != nullptr)
			al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap)/2, al_get_bitmap_height(btMap) / 2, building->xPos() + building->getWidth() / 2, building->yPos() + building->getHeight() / 2, building->getAngle(), 0);
	}
}

void BuildingView::refactor(void) {
	Building* building = (Building*)model;
	string index = to_string((unsigned int)building->getType()) + "_" + to_string((unsigned int)building->getStatus());

	building->setHeight( al_get_bitmap_height(images[index].bitmap) );
	building->setWidth( al_get_bitmap_width(images[index].bitmap) );
}