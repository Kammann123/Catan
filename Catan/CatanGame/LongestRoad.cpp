#include "LongestRoad.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"
#include "CatanGame.h"

LongestRoad::
LongestRoad(CatanGame* game) : FrameUI(LONGEST_ROAD_ID, 0, 0) {
	this->setUIDestroy(false);
	this->game = game;
	this->player = nullptr;
}

void
LongestRoad::assign(Player* player) {
	 
	/* Actualizo los puntajes correspondientes
	*/
	if (player) {
		player->addPoints(LONGEST_ROAD_POINTS);
	}
	if (this->player) {
		this->player->removePoints(LONGEST_ROAD_POINTS);
	}

	/* Actualizo los valores de mi modelo del LongestRoad
	* en cuanto al jugador que lo posee y su ubicacion en el mapa
	*/
	if (player) {
		this->player = player;
	}
	else {
		this->player = nullptr;
	}
	refactor();
}

PlayerId
LongestRoad::who(void) const {
	if (player) {
		return player->getPlayerId();
	}
	else {
		return PlayerId::PLAYER_NONE;
	}
}

void
LongestRoad::refactor(void) {
	if (player) {
		this->setPosition(
			(*player)[POSITION_LONGEST_ROAD].x + player->xPos(),
			(*player)[POSITION_LONGEST_ROAD].y + player->yPos()
		);
	}
	else {

		this->setPosition(
			(*game)[POSITION_LONGEST_ROAD].x,
			(*game)[POSITION_LONGEST_ROAD].y
		);
	}
}