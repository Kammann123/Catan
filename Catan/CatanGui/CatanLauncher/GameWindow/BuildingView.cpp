#include "BuildingView.h"
#include <allegro5/allegro.h>
#include "../../../CatanGame/Player.h"

/**********************
* Imagenes de la View *
**********************/
#define ROAD_0_0 "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_0_0.png"
#define ROAD_30_0 "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_30_0.png"
#define ROAD_90_0 "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_90_0.png"
#define ROAD_150_0 "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_150_0.png"
#define ROAD_0_0_FOCUS "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_0_0_focus.png"
#define ROAD_30_0_FOCUS "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_30_0_focus.png"
#define ROAD_90_0_FOCUS "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_90_0_focus.png"
#define ROAD_150_0_FOCUS "CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_150_0_focus.png"

#define ROAD_0_1	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_0_1.png"
#define ROAD_30_1	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_30_1.png"
#define ROAD_90_1	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_90_1.png"
#define ROAD_150_1	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\bridge_150_1.png"

#define SETTLEMENT_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_settlement.png"
#define SETTLEMENT_FOCUSED_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_settlement_focused.png"
#define SETTLEMENT_SELECTED_IMAGE "CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_settlement_selected.png"
#define SETTLEMENT_OPONENT			"CatanGui\\GUIDesigns\\GameMenu\\buildings\\local_settlement.png"
#define SETTLEMENT_OPONENT_ID	"enemy_settlement"

#define CITY_IMAGE				"CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_city.png"
#define CITY_FOCUSED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_city_focused.png"
#define CITY_SELECTED_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\remote_city_selected.png"
#define CITY_OPONENT		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\local_city.png"
#define CITY_OPONENT_ID		"enemy_city"

#define INDEX(_type, _state) string( to_string((int)BuildingType::_type) + "_" + to_string((int)MouseUI::Status::_state) )

BuildingView::BuildingView(Building * model_) : UIView(model_)
{
	images.clear();

	images.setConfig("0_0", ROAD_0_0);
	images.setConfig("30_0", ROAD_30_0);
	images.setConfig("90_0", ROAD_90_0);
	images.setConfig("150_0", ROAD_150_0);

	images.setConfig("0_0_focus", ROAD_0_0_FOCUS);
	images.setConfig("30_0_focus", ROAD_30_0_FOCUS);
	images.setConfig("90_0_focus", ROAD_90_0_FOCUS);
	images.setConfig("150_0_focus", ROAD_150_0_FOCUS);

	images.setConfig("0_1", ROAD_0_1);
	images.setConfig("30_1", ROAD_30_1);
	images.setConfig("90_1", ROAD_90_1);
	images.setConfig("150_1", ROAD_150_1);

	images.setConfig(INDEX(SETTLEMENT, IDLE), SETTLEMENT_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, FOCUSED), SETTLEMENT_FOCUSED_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, SELECTED), SETTLEMENT_SELECTED_IMAGE);
	images.setConfig(INDEX(SETTLEMENT, DRAGGED), SETTLEMENT_SELECTED_IMAGE);
	images.setConfig(SETTLEMENT_OPONENT_ID, SETTLEMENT_OPONENT);
	images.setConfig(INDEX(CITY, IDLE), CITY_IMAGE);
	images.setConfig(INDEX(CITY, FOCUSED), CITY_FOCUSED_IMAGE);
	images.setConfig(INDEX(CITY, SELECTED), CITY_SELECTED_IMAGE);
	images.setConfig(INDEX(CITY, DRAGGED), CITY_SELECTED_IMAGE);
	images.setConfig(CITY_OPONENT_ID, CITY_OPONENT);
}

void BuildingView::draw(void){
	Building* building = (Building*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	if (model->getVisible()) {
		if (building->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			if (building->getType() != BuildingType::ROAD ) {
				string index = to_string((unsigned int)building->getType()) + "_" + to_string((unsigned int)building->getStatus());
				if (images.has(index)) {
					btMap = images[index].bitmap;
				}
			}
			else {
				if (building->getStatus() == MouseUI::Status::IDLE) {
					switch ((int)building->getAngle()) {
						case 0:
							btMap = images["90_0"].bitmap;
							break;
						case 3:
							btMap = images["0_0"].bitmap;
							break;
						case 1: case 4:
							btMap = images["30_0"].bitmap;
							break;
						case 2: case 5:
							btMap = images["150_0"].bitmap;
							break;
					}
				}
				else {
					switch ((int)building->getAngle()) {
					case 0:
						btMap = images["150_0_focus"].bitmap;
						break;
					case 3:
						btMap = images["150_0_focus"].bitmap;
						break;
					case 1: case 4:
						btMap = images["150_0_focus"].bitmap;
						break;
					case 2: case 5:
						btMap = images["150_0_focus"].bitmap;
						break;
					}
				}
			}
		}
		else {
			switch (building->getType()) {
			case BuildingType::SETTLEMENT:
				if (images.has(SETTLEMENT_OPONENT_ID)) {
					btMap = images[SETTLEMENT_OPONENT_ID].bitmap;
				}
				break;
			case BuildingType::ROAD:
				switch ((int)building->getAngle()) {
				case 0:
					btMap = images["90_1"].bitmap;
					break;
				case 3:
					btMap = images["0_1"].bitmap;
					break;
				case 1: case 4:
					btMap = images["30_1"].bitmap;
					break;
				case 2: case 5:
					btMap = images["150_1"].bitmap;
					break;
				}
				break;
			case BuildingType::CITY:
				if (images.has(CITY_OPONENT_ID)) {
					btMap = images[CITY_OPONENT_ID].bitmap;
				}
				break;
			}
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