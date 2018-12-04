#include "PlayerView.h"

/*Victory Points*/
#define VICTORY_POINTS_IMG	"CatanGui\\GUIDesigns\\GameMenu\\victory_points.png"
#define VICTORY_POINTS_ID	"victory_points"

/*Cartas*/
#define FOREST_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wood_card.png"
#define HILL_CARD_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\brick_card.png"
#define MOUNTAIN_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\ore_card.png"
#define	FIELD_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wheat_card.png"
#define	PASTURES_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wool_card.png"
#define	CARD_BACK_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\card_back.png"

#define	NAME_FONT_ID		"nameFont"
#define NAME_FONT			"CatanGame\\Catan\\CatanGui\\Fonts\\sitka.ttf"
#define	NAME_FONT_SIZE		30
#define	PLAYER_NAME_Y		407
#define PLAYER_ONE_X		18
#define	PLAYER_TWO_X		1072

#define	COUNTER_FONT_ID		"counterFont"
#define COUNTER_FONT		"CatanGame\\Catan\\CatanGui\\Fonts\\LOVES.ttf"
#define	COUNTER_FONT_SIZE	20

#define	VICTORY_PTS_FONT_ID	"victoryPointsFont"
#define	VICTORY_PTS_FONT	COUNTER_FONT
#define	VICTORY_PTS_SIZE	25

#define	PLAYER_FONT_COLOR	237, 241, 196

PlayerView::PlayerView(Player * model_)
{
	images.clear();
	images.setConfig((int)ResourceId::FOREST, FOREST_CARD_IMAGE);
	images.setConfig((int)ResourceId::HILL, HILL_CARD_IMAGE);
	images.setConfig((int)ResourceId::MOUNTAIN, MOUNTAIN_CARD_IMAGE);
	images.setConfig((int)ResourceId::FIELD, FIELD_CARD_IMAGE);
	images.setConfig((int)ResourceId::PASTURES, PASTURES_CARD_IMAGE);
	images.setConfig(VICTORY_POINTS_ID, VICTORY_POINTS_IMG);

	fonts.clear();
	fonts.setConfig(NAME_FONT_ID, NAME_FONT, NAME_FONT_SIZE);
	fonts.setConfig(COUNTER_FONT_ID, COUNTER_FONT, COUNTER_FONT_SIZE);
	fonts.setConfig(VICTORY_PTS_FONT_ID, VICTORY_PTS_FONT, VICTORY_PTS_SIZE);
}

PlayerView::~PlayerView()
{
}

void PlayerView::draw(void)
{
	Player* player = (Player*)model;
	ALLEGRO_BITMAP * btMap;
	ALLEGRO_FONT * fontPlayer;
	ALLEGRO_FONT * fontCounter;
	ALLEGRO_FONT * fontVP;
	ALLEGRO_COLOR * color = al_map_rgb(PLAYER_FONT_COLOR);
	PlayerId playerId = player->getPlayerId();
	unsigned int resourceAmount;

	/*Se dibujan las cartas*/
	for (ResourceCard* resourceCard : player->showCards()) {	//Se itera la lista de cartas
		/*Se busca la imagen de la carta*/
		if (images.has((int)resourceCard->getResourceId())) {
			btMap = images[((int)resourceCard->getResourceId())].bitmap;
		}
		/*Se dibuja la carta*/
		if (btMap != nullptr)
			al_draw_bitmap(btMap, resourceCard->xPos(), resourceCard->yPos(), 0);
		btMap = nullptr;	//Se reinicia
		/*Se busca la fuente del contador de recursos*/
		if (fonts.has(COUNTER_FONT_ID)) {
			fontCounter = fonts[COUNTER_FONT_ID].font;
		}
		/*Se busca la cantidad de cartas de dicho recurso */
		resourceAmount = player->getResourceCount(resourceCard->getResourceId());
		if (fontCounter != nullptr)
		{
			char buffer[5];
			const char *str = itoa(resourceAmount, buffer, 10);
			int textWidth = al_get_text_width(fontCounter, str);
			int textHeight = al_get_text_height(fontCounter, str);
			int bitmapWidth = al_get_bitmap_width(btMap);
			al_draw_text(fontCounter,color, resourceCard->xPos() + bitmapWidth / 2 - textWidth/2, resourceCard->yPos() - 5 - textHeight, ALLEGRO_ALIGN_CENTRE, str);	//Se escribe la cantidad de cartas de dicho recurso
		}		
	}	

	/*Se dibujan los victory points y los nombres de los jugadores*/

	/*Se busca la imagen de los victory points*/
	if (images.has(VICTORY_POINTS_ID) {
		btMap = images[VICTORY_POINTS_ID].bitmap;	//La imagen queda almacenada
	}
	/*Se busca la fuente del nombre del player*/
	if (fonts.has(NAME_FONT_ID)) {
		fontPlayer = fonts[NAME_FONT_ID].font;	//La fuente queda almacenada
	}
	/*Se busca la fuente del numero de victoryPoints*/
	if (fonts.has(VICTORY_PTS_FONT_ID)) {
		fontVP = fonts[VICTORY_PTS_FONT_ID].font;	//La fuente queda almacenada
	}
	if (fontPlayer != nullptr) {
		if (fontVP != nullptr){
			if (btMap != nullptr){
				
				int widthPlayerName = al_get_text_width(fontPlayer, player->getName().c_str());
				char buffer[5];
				const char *strVP = itoa(player->getVictoryPoints(), buffer, 10);
				int btMapVPWidth = al_get_bitmap_width(btMap);
				switch (playerId) {
				case PLAYER_ONE:
					al_draw_text(fontPlayer, color, PLAYER_ONE_X, PLAYER_NAME_Y, ALLEGRO_ALIGN_LEFT, player->getName().c_str());	//Texto nombre jugador
					al_draw_text(fontVP, color, PLAYER_ONE_X + widthPlayerName + 20 + btMapVPWidth/2, PLAYER_NAME_Y, ALLEGRO_ALIGN_CENTRE, strVP);	//Texto cantidad de VPS
					al_draw_bitmap(btMap, PLAYER_ONE_X + widthPlayerName + 20, PLAYER_NAME_Y, 0);	//IMAGEN VPS
					break;
				case PLAYER_TWO:
					al_draw_text(fontPlayer, color, PLAYER_TWO_X - widthPlayerName, PLAYER_NAME_Y, ALLEGRO_ALIGN_LEFT, player->getName().c_str());	//Texto nombre jugador	
					al_draw_text(fontVP, color, PLAYER_ONE_X - widthPlayerName - 20 + btMapVPWidth / 2, PLAYER_NAME_Y, ALLEGRO_ALIGN_CENTRE, strVP);	//Texto cantidad de VPS
					al_draw_bitmap(btMap, PLAYER_TWO_X - widthPlayerName - 20, PLAYER_NAME_Y, 0);	//Imagen VPS
					break;
				}
			}
		}
	}
}

void PlayerView::updateModelValues(void)
{
}
