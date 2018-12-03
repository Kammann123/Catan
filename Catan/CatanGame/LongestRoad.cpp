#include "LongestRoad.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"
#include "CatanGame.h"

LongestRoad::
LongestRoad(CatanGame* game) : FrameUI(LONGEST_ROAD_ID, 0, 0) {
	this->game = game;
	this->player = nullptr;
}

void
LongestRoad::assign(Player* player) {
	if (player) {
		this->player = player;
		this->setPosition(
			(*player)[POSITION_LONGEST_ROAD].x,
			(*player)[POSITION_LONGEST_ROAD].y
		);
	}
	else {
		this->player = nullptr;
		this->setPosition(
			(*game)[POSITION_LONGEST_ROAD].x,
			(*game)[POSITION_LONGEST_ROAD].y
		);
	}
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