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
#define CARD_BACK_ID		"card_Back"

/*********************
* Fuentes de la View *
*********************/
#define	NAME_FONT_ID		"nameFont"
#define NAME_FONT			"CatanGui\\Fonts\\press.otf"
#define	NAME_FONT_SIZE		30
#define LOCAL_COLOR			"local_color"
#define	REMOTE_COLOR		"remote_color"
#define	COUNTER_FONT_ID		"counterFont"
#define COUNTER_FONT		"CatanGui\\Fonts\\SuperMario256.ttf"
#define	COUNTER_FONT_SIZE	25
#define	VICTORY_PTS_FONT_ID	"victoryPointsFont"
#define	VICTORY_PTS_FONT	COUNTER_FONT
#define	VICTORY_PTS_SIZE	25
#define	PLAYER_FONT_COLOR	"fontColor"

#define NAME_STRING_MAX_LENGHT 10
#define TRIANGLE_WIDTH 15

PlayerView::PlayerView(Player * model_) : UIView(model_)
{
	images.clear();
	images.setConfig((int)ResourceId::FOREST, FOREST_CARD_IMAGE);
	images.setConfig((int)ResourceId::HILL, HILL_CARD_IMAGE);
	images.setConfig((int)ResourceId::MOUNTAIN, MOUNTAIN_CARD_IMAGE);
	images.setConfig((int)ResourceId::FIELD, FIELD_CARD_IMAGE);
	images.setConfig((int)ResourceId::PASTURES, PASTURES_CARD_IMAGE);
	images.setConfig(CARD_BACK_ID, CARD_BACK_IMAGE);
	images.setConfig(VICTORY_POINTS_ID, VICTORY_POINTS_IMG);

	fonts.clear();
	fonts.setConfig(NAME_FONT_ID, NAME_FONT, NAME_FONT_SIZE);
	fonts.setConfig(COUNTER_FONT_ID, COUNTER_FONT, COUNTER_FONT_SIZE);
	fonts.setConfig(VICTORY_PTS_FONT_ID, VICTORY_PTS_FONT, VICTORY_PTS_SIZE);

	colors.clear();
	colors.setConfig(PLAYER_FONT_COLOR, 255, 255, 100);
	colors.setConfig(LOCAL_COLOR, 79, 100, 170);
	colors.setConfig(REMOTE_COLOR, 160, 70, 70);
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
	ALLEGRO_COLOR nameColor = playerId == PlayerId::PLAYER_ONE ? colors[LOCAL_COLOR].color : colors[REMOTE_COLOR].color;

	/* Se dibuja el nombre del jugador */
	fontPlayer = fonts[NAME_FONT_ID].font;
	string playerName = player->getName();

	if (playerName.length() > (NAME_STRING_MAX_LENGHT + 3))
	{
		while (playerName.length() > NAME_STRING_MAX_LENGHT)
		{
			playerName.pop_back();
		}

		playerName += "...";
	}
	

	al_draw_text(fontPlayer, nameColor, (*player)[PLAYER_NAME].x + player->xPos(), (*player)[PLAYER_NAME].y + player->yPos(), 0, playerName.c_str());

	/* Se dibuja el indicador de turno (si es necesario) */

	if (player->getPlayerId() == player->getGame()->getTurn())
	{
		al_draw_filled_triangle(
			(*player)[PLAYER_NAME].x + player->xPos() - TRIANGLE_WIDTH, (*player)[PLAYER_NAME].y + player->yPos() + 11,
			(*player)[PLAYER_NAME].x + player->xPos(), (*player)[PLAYER_NAME].y + player->yPos() + al_get_font_line_height(fontPlayer) / 2,
			(*player)[PLAYER_NAME].x + player->xPos() - TRIANGLE_WIDTH, (*player)[PLAYER_NAME].y + player->yPos() + al_get_font_line_height(fontPlayer) - 11,
			color
			); 
	}

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
	al_draw_text(fontCounter, color, (*player)[PLAYER_SETTLEMENTS].x + player->xPos() + 20, (*player)[PLAYER_CITY].y - counterOffset + player->yPos() + 15, 0, settlementCount.c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_ROADS].x + player->xPos() + 20, (*player)[PLAYER_CITY].y - counterOffset + player->yPos() + 15, 0, roadsCount.c_str());
	al_draw_text(fontCounter, color, (*player)[PLAYER_CITY].x + player->xPos() + 20, (*player)[PLAYER_CITY].y - counterOffset + player->yPos() + 15, 0, cityCount.c_str());

	/* Dibujo las cantidades de las cartas */
	counterOffset = 20;
	if (player->getPlayerId() == PlayerId::PLAYER_ONE) {
		al_draw_text(fontCounter, color, (*player)[PLAYER_ORE].x + player->xPos(), (*player)[PLAYER_ORE].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::MOUNTAIN)).c_str());
		al_draw_text(fontCounter, color, (*player)[PLAYER_BRICK].x + player->xPos(), (*player)[PLAYER_BRICK].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::HILL)).c_str());
		al_draw_text(fontCounter, color, (*player)[PLAYER_WOOL].x + player->xPos(), (*player)[PLAYER_WOOL].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::PASTURES)).c_str());
		al_draw_text(fontCounter, color, (*player)[PLAYER_GRAIN].x + player->xPos(), (*player)[PLAYER_GRAIN].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::FIELD)).c_str());
		al_draw_text(fontCounter, color, (*player)[PLAYER_LUMBER].x + player->xPos(), (*player)[PLAYER_LUMBER].y - counterOffset + player->yPos(), 0, to_string(player->getResourceCount(ResourceId::FOREST)).c_str());
	}
	
	/* Dibujo las cartas */
	btMap = player->getPlayerId() == PlayerId::PLAYER_ONE ? images[(unsigned int)ResourceId::MOUNTAIN].bitmap : images[CARD_BACK_ID].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_ORE].x + player->xPos(), (*player)[PLAYER_ORE].y + player->yPos(), 0);
	btMap = player->getPlayerId() == PlayerId::PLAYER_ONE ? images[(unsigned int)ResourceId::HILL].bitmap : images[CARD_BACK_ID].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_BRICK].x + player->xPos(), (*player)[PLAYER_BRICK].y + player->yPos(), 0);
	btMap = player->getPlayerId() == PlayerId::PLAYER_ONE ? images[(unsigned int)ResourceId::PASTURES].bitmap : images[CARD_BACK_ID].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_WOOL].x + player->xPos(), (*player)[PLAYER_WOOL].y + player->yPos(), 0);
	btMap = player->getPlayerId() == PlayerId::PLAYER_ONE ? images[(unsigned int)ResourceId::FIELD].bitmap : images[CARD_BACK_ID].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_GRAIN].x + player->xPos(), (*player)[PLAYER_GRAIN].y + player->yPos(), 0);
	btMap = player->getPlayerId() == PlayerId::PLAYER_ONE ? images[(unsigned int)ResourceId::FOREST].bitmap : images[CARD_BACK_ID].bitmap;
	al_draw_bitmap(btMap, (*player)[PLAYER_LUMBER].x + player->xPos(), (*player)[PLAYER_LUMBER].y + player->yPos(), 0);
}