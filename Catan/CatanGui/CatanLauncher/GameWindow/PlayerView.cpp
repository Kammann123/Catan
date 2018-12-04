#include "PlayerView.h"
#include "GameWindow.h"
#include "allegro5/allegro.h"

#include <string>

using namespace std;

/**********************
* Imagenes de la View *
**********************/
#define VICTORY_POINTS_IMG	"CatanGui\\GUIDesigns\\GameMenu\\vp.png"
#define VICTORY_POINTS_ID	"victory_points"
#define FOREST_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wood_card.png"
#define HILL_CARD_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\brick_card.png"
#define MOUNTAIN_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\ore_card.png"
#define	FIELD_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wheat_card.png"
#define	PASTURES_CARD_IMAGE	"CatanGui\\GUIDesigns\\GameMenu\\cards\\wool_card.png"
#define	CARD_BACK_IMAGE		"CatanGui\\GUIDesigns\\GameMenu\\cards\\card_back.png"

/*********************
* Fuentes de la View *
*********************/
#define	NAME_FONT_ID		"nameFont"
#define NAME_FONT			"CatanGui\\Fonts\\sitka.ttf"
#define	NAME_FONT_SIZE		30
#define	COUNTER_FONT_ID		"counterFont"
#define COUNTER_FONT		"CatanGui\\Fonts\\SuperMario256.ttf"
#define	COUNTER_FONT_SIZE	25
#define	VICTORY_PTS_FONT_ID	"victoryPointsFont"
#define	VICTORY_PTS_FONT	COUNTER_FONT
#define	VICTORY_PTS_SIZE	25
#define	PLAYER_FONT_COLOR	"fontColor"

PlayerView::PlayerView(Player * model_) : UIView(model_)
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

	colors.clear();
	colors.setConfig(PLAYER_FONT_COLOR, 237, 241, 196);
}

void PlayerView::draw(void)
{
	Player* player = (Player*)model;
	ALLEGRO_FONT * fontCounter;
	ALLEGRO_FONT * fontPlayer;
	ALLEGRO_BITMAP * btMap;
	ALLEGRO_FONT * fontVP;
	ALLEGRO_COLOR color = colors[PLAYER_FONT_COLOR].color;
	PlayerId playerId = player->getPlayerId();
	unsigned int resourceAmount;

	/* Se dibuja el nombre del jugador */
	fontPlayer = fonts[NAME_FONT_ID].font;
	al_draw_text(fontPlayer, color, (*player)[PLAYER_NAME].x + player->xPos(), (*player)[PLAYER_NAME].y + player->yPos(), 0, player->getName().c_str());

	/* Se dibujan los victory points del jugador */
	btMap = images[VICTORY_POINTS_ID].bitmap;
	double xOffset = al_get_bitmap_width(btMap) / 2 - 5;
	double yOffset = al_get_bitmap_height(btMap) / 2 - 8;
	fontVP = fonts[VICTORY_PTS_FONT_ID].font;
	al_draw_bitmap(btMap, (*player)[PLAYER_VICTORY_POINTS].x + player->xPos(), (*player)[PLAYER_VICTORY_POINTS].y + player->yPos(), 0);
	al_draw_text(fontVP, color, (*player)[PLAYER_VICTORY_POINTS].x + player->xPos() + xOffset, (*player)[PLAYER_VICTORY_POINTS].y + player->yPos() + yOffset, 0, to_string(player->getVictoryPoints()).c_str());

	/* Dibujo las cantidades de los buildings */
	fontCounter = fonts[COUNTER_FONT_ID].font;
	double counterOffset = 40;
	string settlementCount = to_string(player->hasSettlements());
	string roadsCount = to_string(player->hasRoads());
	string cityCount = to_string(player->hasCities());
	al_draw_text(fontCounter, color, (*player)[PLAYER_SETTLEMENTS].x + player->xPos(), (*player)[PLAYER_SETTLEMENTS].y - counterOffset + player->yPos(), 0, settlementCount.c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_ROADS].x + player->xPos(), (*player)[PLAYER_ROADS].y - counterOffset + player->yPos(), 0, roadsCount.c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_CITY].x + player->xPos(), (*player)[PLAYER_CITY].y - counterOffset + player->yPos(), 0, cityCount.c_str());

	/* Dibujo las cantidades de las cartas */
	counterOffset = 20;
	al_draw_text(fontCounter, color, (*player)[PLAYER_ORE].x + player->xPos(), (*player)[PLAYER_ORE].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::MOUNTAIN)).c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_BRICK].x + player->xPos(), (*player)[PLAYER_BRICK].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::HILL)).c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_WOOL].x + player->xPos(), (*player)[PLAYER_WOOL].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::FIELD)).c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_GRAIN].x + player->xPos(), (*player)[PLAYER_GRAIN].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::PASTURES)).c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_LUMBER].x + player->xPos(), (*player)[PLAYER_LUMBER].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::FOREST)).c_str());

	/* Dibujo las cartas */
	btMap = images[(unsigned int)ResourceId::MOUNTAIN].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_ORE].x + player->xPos(), (*player)[PLAYER_ORE].y + player->yPos(), 0);
	btMap = images[(unsigned int)ResourceId::HILL].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_BRICK].x + player->xPos(), (*player)[PLAYER_BRICK].y + player->yPos(), 0);
	btMap = images[(unsigned int)ResourceId::FIELD].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_WOOL].x + player->xPos(), (*player)[PLAYER_WOOL].y + player->yPos(), 0);
	btMap = images[(unsigned int)ResourceId::PASTURES].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_GRAIN].x + player->xPos(), (*player)[PLAYER_GRAIN].y + player->yPos(), 0);
	btMap = images[(unsigned int)ResourceId::FOREST].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_LUMBER].x + player->xPos(), (*player)[PLAYER_LUMBER].y + player->yPos(), 0);
}