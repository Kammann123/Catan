#include "CatanMapView.h"
#include <allegro5/allegro.h>


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
#define	TOKEN_7_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\7token.png"
#define	TOKEN_8_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\8token.png"
#define	TOKEN_9_IMG			"CatanGui\\GUIDesigns\\GameMenu\\tokens\\9token.png"
#define	TOKEN_10_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\10token.png"
#define	TOKEN_11_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\11token.png"
#define	TOKEN_12_IMG		"CatanGui\\GUIDesigns\\GameMenu\\tokens\\12token.png"

/******************************************COMPLETAR****************************************/
#define NORMAL_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
#define	WHEAT_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
#define	SHEEP_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
#define	BRICK_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
#define	STONE_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
#define	WOOD_SEA_IMG		"CatanGui\\GUIDesigns\\GameMenu\\seas\\"
CatanMapView::CatanMapView(CatanMap * model_) : UIView(model_)
{
	images.clear();
	/*Config imagenes de tierras*/
	images.setConfig(ResourceId::FOREST, FOREST_LAND_IMG);
	images.setConfig(ResourceId::HILL, HILL_LAND_IMG);
	images.setConfig(ResourceId::MOUNTAIN, MOUNTAIN_LAND_IMG);
	images.setConfig(ResourceId::FIELD, FIELD_LAND_IMG);
	images.setConfig(ResourceId::PASTURES, PASTURES_LAND_IMG);
	images.setConfig(ResourceId::DESERT, DESERT_LAND_IMG);

	/*Config imagenes de tokens*/
	images.setConfig(2, TOKEN_2_IMG);
	images.setConfig(3, TOKEN_3_IMG);
	images.setConfig(4, TOKEN_4_IMG);
	images.setConfig(5, TOKEN_5_IMG);
	images.setConfig(6, TOKEN_6_IMG);
	images.setConfig(7, TOKEN_7_IMG);
	images.setConfig(8, TOKEN_8_IMG);
	images.setConfig(9, TOKEN_9_IMG);
	images.setConfig(10, TOKEN_10_IMG);
	images.setConfig(11, TOKEN_11_IMG);
	images.setConfig(12, TOKEN_12_IMG);

	/*Config imagenes de mar*/
	images.setConfig(SeaId::NORMAL, NORMAL_SEA_IMG);
	images.setConfig(SeaId::WHEAT, WHEAT_SEA_IMG);
	images.setConfig(SeaId::SHEEP, SHEEP_SEA_IMG);
	images.setConfig(SeaId::BRICK, BRICK_SEA_IMG);
	images.setConfig(SeaId::STONE, STONE_SEA_IMG);
	images.setConfig(SeaId::WOOD, WOOD_SEA_IMG);
}

CatanMapView::~CatanMapView()
{
}

void CatanMapView::draw(void)
{
	CatanMap* catanMap = (CatanMap*)model;
	ALLEGRO_BITMAP * btMap = nullptr;
	ALLEGRO_BITMAP * tokenBtMap = nullptr;
	std::map<string, position_t> mymap = CatanMap::screen();
	std::map<string, position_t>::iterator it;
	std::map<Coord, unsigned char> tokenMap = CatanMap::getTokens();
	std::map<Coord, unsigned char>::iterator tokenIt;
	position_t resourcePosition;
	unsigned char tokenValue;
	if (model->getVisible())
	{
		/*Se ciclan los mares*/
		for (SeaHex* seaHex : CatanMap::seas()) {
			it = mymap.find(seaHex->getCoord());

			if (it != mymap.end()) {				//Si existe
				resourcePosition = it->second;		//Se guarda la posicion y el angulo
				/*Se busca la imagen del mar*/
				if (images.has(seaHex->getDocks())) {
					btMap = images[seaHex->getDocks()].bitmap;
				}
				/*Se dibuja la imagen*/
				if (btMap != nullptr)
					al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap) / 2, al_get_bitmap_height(btMap) / 2, resourcePosition.x, resourcePosition.y, resourcePosition.info, 0);
				btMap = nullptr;		//Se reinicia el bitmap
			}

		}
		/*Se ciclan las tierras*/
		for (ResourceHex* resourceHex : CatanMap::lands()) {
			it = mymap.find(resourceHex->getCoord());
			tokenIt = tokenMap.find(seaHex->getCoord());
			if (it != mymap.end()) {					//Si existe
				resourcePosition = it->second;			//Se guarda la posicion y el angulo
				/*Se busca la imagen de la tierra*/
				if (images.has(resourceHex->getResource())) {
					btMap = images[resourceHex->getResource()].bitmap;
				}
				/*Se dibuja la imagen*/
				if (btMap != nullptr)
					al_draw_rotated_bitmap(btMap, al_get_bitmap_width(btMap) / 2, al_get_bitmap_height(btMap) / 2, resourcePosition.x, resourcePosition.y, resourcePosition.info, 0);
				btMap = nullptr;	//Se reinicia el bitmap

				if (tokenIt != tokenMap.end()) {		//Si existe
					tokenValue = tokenIt->second;		//Se guarda el numero del token
					/*Se busca la imagen del token*/
					if (images.has((int)tokenValue)) {
						tokenBtMap = images[(int)tokenValue].bitmap;
					}
					/*Se dibuja la imagen*/
					if (tokenBtMap != nullptr)
						al_draw_bitmap(tokenBtMap, resourcePosition.x, resourcePosition.y, 0);
					tokenBtMap = nullptr;		//Se reinicia el bitmap
				}
			}
		}
	}
	


}

void CatanMapView::updateModelValues(void)
{
}
