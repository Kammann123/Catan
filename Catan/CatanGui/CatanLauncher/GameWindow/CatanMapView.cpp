#include "CatanMapView.h"
#include <allegro5/allegro.h>

#define MAP_HEX_IMG			"CatanGui\\GUIDesigns\\GameMenu\\backHex.png"
#define MAP_HEX_ID			"we_esto_nadie_lo_leera"

#define FOREST_LAND_IMG		"CatanGui\\GUIDesigns\\GameMenu\\lands\\forest.png"
#define HILL_LAND_IMG		"CatanGui\\GUIDesigns\\GameMenu\\lands\\brick.png"
#define MOUNTAIN_LAND_IMG	"CatanGui\\GUIDesigns\\GameMenu\\lands\\ore.png"
#define	FIELD_LAND_IMG		"CatanGui\\GUIDesigns\\GameMenu\\lands\\wheat.png"
#define	PASTURES_LAND_IMG	"CatanGui\\GUIDesigns\\GameMenu\\lands\\pastures.png"
#define	DESERT_LAND_IMG		"CatanGui\\GUIDesigns\\GameMenu\\lands\\desert.png"

#define	TOKEN_2_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\2token.png"
#define	TOKEN_3_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\3token.png"
#define	TOKEN_4_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\4token.png"
#define	TOKEN_5_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\5token.png"
#define	TOKEN_6_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\6token.png"
#define	TOKEN_8_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\8token.png"
#define	TOKEN_9_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\9token.png"
#define	TOKEN_10_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\10token.png"
#define	TOKEN_11_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\11token.png"
#define	TOKEN_12_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\12token.png"

#define NORMAL_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\normal_sea.png"
#define	WHEAT_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\wheat_normal_sea.png"
#define	SHEEP_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\wool_normal_sea.png"
#define	BRICK_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\brick_normal_sea.png"
#define	STONE_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\ore_sea.png"
#define	WOOD_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\sea\\wood_sea.png"

#define SEA_INDEX_OFFSET	1234

#define RADIAN(x)	(((x)/360) * 3.1415 * 2)

CatanMapView::CatanMapView(CatanMap * model_) : UIView(model_){
	images.clear();

	/*Config images de mapa*/
	images.setConfig(MAP_HEX_ID, MAP_HEX_IMG);

	/*Config imagenes de tierras*/
	images.setConfig((unsigned int)ResourceId::FOREST, FOREST_LAND_IMG);
	images.setConfig((unsigned int)ResourceId::HILL, HILL_LAND_IMG);
	images.setConfig((unsigned int)ResourceId::MOUNTAIN, MOUNTAIN_LAND_IMG);
	images.setConfig((unsigned int)ResourceId::FIELD, FIELD_LAND_IMG);
	images.setConfig((unsigned int)ResourceId::PASTURES, PASTURES_LAND_IMG);
	images.setConfig((unsigned int)ResourceId::DESERT, DESERT_LAND_IMG);

	/*Config imagenes de tokens*/
	images.setConfig(2, TOKEN_2_IMG);
	images.setConfig(3, TOKEN_3_IMG);
	images.setConfig(4, TOKEN_4_IMG);
	images.setConfig(5, TOKEN_5_IMG);
	images.setConfig(6, TOKEN_6_IMG);
	images.setConfig(8, TOKEN_8_IMG);
	images.setConfig(9, TOKEN_9_IMG);
	images.setConfig(10, TOKEN_10_IMG);
	images.setConfig(11, TOKEN_11_IMG);
	images.setConfig(12, TOKEN_12_IMG);

	/*Config imagenes de mar*/
	images.setConfig((unsigned int)SeaId::NORMAL + SEA_INDEX_OFFSET, NORMAL_SEA_IMG);
	images.setConfig((unsigned int)SeaId::WHEAT + SEA_INDEX_OFFSET, WHEAT_SEA_IMG);
	images.setConfig((unsigned int)SeaId::SHEEP + SEA_INDEX_OFFSET, SHEEP_SEA_IMG);
	images.setConfig((unsigned int)SeaId::BRICK + SEA_INDEX_OFFSET, BRICK_SEA_IMG);
	images.setConfig((unsigned int)SeaId::STONE + SEA_INDEX_OFFSET, STONE_SEA_IMG);
	images.setConfig((unsigned int)SeaId::WOOD + SEA_INDEX_OFFSET, WOOD_SEA_IMG);
}

void CatanMapView::draw(void) {
	CatanMap* catanMap = (CatanMap*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	ALLEGRO_BITMAP * tokenBtMap = nullptr;
	std::map<string, position_t> mymap = catanMap->screen();
	std::map<string, position_t>::iterator it;
	std::map<Coord, unsigned char> tokenMap = catanMap->getTokens();
	std::map<Coord, unsigned char>::iterator tokenIt;
	position_t resourcePosition;
	unsigned char tokenValue;

	if (model->getVisible()){

		/* Se ciclan las tierras */
		for (ResourceHex* resourceHex : catanMap->lands()) {
			it = mymap.find(resourceHex->getCoord().getCoords());
			tokenIt = tokenMap.find(resourceHex->getCoord());
			if (it != mymap.end()) {					//Si existe
				resourcePosition = it->second;			//Se guarda la posicion y el angulo
														/*Se busca la imagen de la tierra*/
				if (images.has((unsigned int)resourceHex->getResource())) {
					btMap = images[(unsigned int)resourceHex->getResource()].bitmap;
				}
				/*Se dibuja la imagen*/
				if (btMap != nullptr)
					al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap) / 2, al_get_bitmap_height(btMap) / 2, resourcePosition.x + catanMap->xPos(), resourcePosition.y + catanMap->yPos(), resourcePosition.info, 0);
				btMap = nullptr;	//Se reinicia el bitmap

				if (tokenIt != tokenMap.end()) {		//Si existe
					tokenValue = tokenIt->second;		//Se guarda el numero del token
														/*Se busca la imagen del token*/
					if (images.has((int)tokenValue)) {
						tokenBtMap = images[(int)tokenValue].bitmap;
					}
					/*Se dibuja la imagen*/
					if (tokenBtMap != nullptr)
						al_draw_rotated_bitmap(tokenBtMap, al_get_bitmap_width(tokenBtMap) / 2, al_get_bitmap_height(tokenBtMap) / 2, resourcePosition.x + catanMap->xPos(), resourcePosition.y + catanMap->yPos(), 0, 0);
					tokenBtMap = nullptr;		//Se reinicia el bitmap
				}
			}
		}

		/* Se ciclan los mares */
		for (SeaHex* seaHex : catanMap->seas()) {
			it = mymap.find(seaHex->getCoord().getCoords());

			if (it != mymap.end()) {

				resourcePosition = it->second;
				if (images.has((unsigned int)seaHex->getDocks() + SEA_INDEX_OFFSET)) {
					btMap = images[(unsigned int)seaHex->getDocks() + SEA_INDEX_OFFSET].bitmap;
				}

				if (btMap != nullptr) {
					al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap) / 2, al_get_bitmap_height(btMap) / 2, resourcePosition.x + catanMap->xPos(), resourcePosition.y + catanMap->yPos(), RADIAN(resourcePosition.info), 0);
				}
				btMap = nullptr;
			}
		}

		/* Imprimimos mapa */
		btMap = images[MAP_HEX_ID].bitmap;
		al_draw_bitmap(btMap, catanMap->xPos() + 81, catanMap->yPos() + 53, 0);
	}
}