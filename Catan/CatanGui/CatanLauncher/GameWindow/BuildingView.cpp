#include "BuildingView.h"
#include <allegro5/allegro.h>
#include "../../../CatanGame/Player.h"

/**********************
* Imagenes de la View *
**********************/
#define ROAD_30_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_30_normal.png"
#define ROAD_30_FOCUS		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_30_focused.png"
#define ROAD_30_OPONENT		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_30_oponent.png"
#define ROAD_90_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_90_normal.png"
#define ROAD_90_FOCUS		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_90_focused.png"
#define ROAD_90_OPONENT		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_90_oponent.png"
#define ROAD_150_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_150_normal.png"
#define ROAD_150_FOCUS		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_150_focused.png"
#define ROAD_150_OPONENT	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\road_150_oponent.png"

#define SETTLEMENT_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_normal.png"
#define SETTLEMENT_FOCUS		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_focused.png"
#define SETTLEMENT_SELECTED		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_selected.png"
#define SETTLEMENT_OPONENT		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\settlement_oponent.png"

#define CITY_NORMAL		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_normal.png"
#define CITY_FOCUS		"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_focused.png"
#define CITY_SELECTED	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_selected.png"
#define CITY_OPONENT	"CatanGui\\GUIDesigns\\GameMenu\\buildings\\city_oponent.png"

#define INDEX(_type, _state) string( to_string((int)BuildingType::_type) + "_" + to_string((int)MouseUI::Status::_state) )

BuildingView::BuildingView(Building * model_) : UIView(model_){
	/* Se limpian las imagenes por defecto de la clase */
	images.clear();

	/**********************************************
	* Se precargas las imagenes del building view *
	**********************************************/
	images.setConfig("road_30_normal", ROAD_30_NORMAL);
	images.setConfig("road_30_focus", ROAD_30_FOCUS);
	images.setConfig("road_30_oponent", ROAD_30_OPONENT);
	images.setConfig("road_90_normal", ROAD_90_NORMAL);
	images.setConfig("road_90_focus", ROAD_90_FOCUS);
	images.setConfig("road_90_oponent", ROAD_90_OPONENT);
	images.setConfig("road_150_normal", ROAD_150_NORMAL);
	images.setConfig("road_150_focus", ROAD_150_FOCUS);
	images.setConfig("road_150_oponent", ROAD_150_OPONENT);

	images.setConfig("settlement_normal", SETTLEMENT_NORMAL);
	images.setConfig("settlement_focus", SETTLEMENT_FOCUS);
	images.setConfig("settlement_selected", SETTLEMENT_SELECTED);
	images.setConfig("settlement_oponent", SETTLEMENT_OPONENT);

	images.setConfig("city_normal", CITY_NORMAL);
	images.setConfig("city_focus", CITY_FOCUS);
	images.setConfig("city_selected", CITY_SELECTED);
	images.setConfig("city_oponent", CITY_OPONENT);
}

void BuildingView::draw(void){

	/**********************************************
	* Recupero el modelo al cual observa la View
	* y creo el bitmap vacio en el cual se cargara
	* la imagen del building actual.
	**********************************************/
	Building* building = (Building*)model;
	ALLEGRO_BITMAP* bitmap = nullptr;

	/* Verifico que el modelo este visible */
	if (model->getVisible()) {
		/* Si la construccion es del primer o segundo jugador... */
		if (building->getPlayer()->getPlayerId() == PlayerId::PLAYER_ONE) {
			/* Veo que tipo de construccion es */
			switch (building->getType()) {
				case BuildingType::CITY:
					switch (building->getStatus()) {
					case MouseUI::Status::IDLE:
						bitmap = images["city_normal"].bitmap;
						break;
					case MouseUI::Status::FOCUSED:
						bitmap = images["city_focus"].bitmap;
						break;
					case MouseUI::Status::SELECTED:
					case MouseUI::Status::DRAGGED:
						bitmap = images["city_selected"].bitmap;
						break;
					}
					break;
				case BuildingType::SETTLEMENT:
					switch (building->getStatus()) {
						case MouseUI::Status::IDLE:
							bitmap = images["settlement_normal"].bitmap;
							break;
						case MouseUI::Status::FOCUSED:
							bitmap = images["settlement_focus"].bitmap;
							break;
						case MouseUI::Status::SELECTED:
						case MouseUI::Status::DRAGGED:
							bitmap = images["settlement_selected"].bitmap;
							break;
					}
					break;
				case BuildingType::ROAD:
					/* Me fijo que orientacion tiene */
					switch (building->getAngle()) {
						case 120: case 300:
							if (building->getStatus() == MouseUI::Status::IDLE) {
								bitmap = images["road_30_normal"].bitmap;
							}
							else {
								bitmap = images["road_30_focus"].bitmap;
							}
							break;
						case 90: case 0:
							if (building->getStatus() == MouseUI::Status::IDLE) {
								bitmap = images["road_90_normal"].bitmap;
							}
							else {
								bitmap = images["road_90_focus"].bitmap;
							}
							break;
						case 240: case 60:
							if (building->getStatus() == MouseUI::Status::IDLE) {
								bitmap = images["road_150_normal"].bitmap;
							}
							else {
								bitmap = images["road_150_focus"].bitmap;
							}
							break;
					}
					break;
			}
		}
		else {
			/* Verifico que tipo de construccion es para poder imprimir */
			switch (building->getType()) {
				case BuildingType::SETTLEMENT:
					bitmap = images["settlement_oponent"].bitmap;
					break;
				case BuildingType::CITY:
					bitmap = images["city_oponent"].bitmap;
					break;
				case BuildingType::ROAD:
					/* Busco la orientacion del camino para deficir que bitmap uso */
					switch (building->getAngle()) {
						case 120: case 300:
							bitmap = images["road_30_oponent"].bitmap;
							break;
						case 90: case 0:
							bitmap = images["road_90_oponent"].bitmap;
							break;
							case 60: case 240:
							bitmap = images["road_150_oponent"].bitmap;
							break;
					}
					break;
			}
		}
	}

	/* Se dibuja la imagen correspondientemente en la ubicacion */
	al_draw_bitmap(
		bitmap,
		building->xPos(),
		building->yPos(),
		0
	);
}

void BuildingView::refactor(void) {
	Building* building = (Building*)model;
	string index;

	/* Busco el tipo de imagen usada actualmente */
	switch (building->getType()) {
		case BuildingType::ROAD:
			index = "road_90_normal";
			break;
		case BuildingType::SETTLEMENT:
			index = "settlement_normal";
			break;
		case BuildingType::CITY:
			index = "city_normal";
			break;
	}

	/* Actualizo los tamaños en funcion del bitmpa obtenido! */
	building->setHeight( al_get_bitmap_height(images[index].bitmap) );
	building->setWidth( al_get_bitmap_width(images[index].bitmap) );
}