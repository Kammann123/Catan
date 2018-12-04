#include "ResourceCard.h"
#include "Player.h"
#include "CatanGame.h"

ResourceCard::
ResourceCard(ResourceId resourceId, CatanGame* game) : FrameUI("", 0, 0) {
	this->resourceId = resourceId;
	this->player = nullptr;
	this->game = game;
}

void
ResourceCard::assign(Player* player) {
	if (player) {
		this->player = player;
	}
	else {
		this->player = nullptr;
	}
}

ResourceId
ResourceCard::getResourceId(void) {
	return resourceId;
}

const char* 
ResourceCard::getResource(void) {
	return resourceStrings[(unsigned int)resourceId];
}

Player*
ResourceCard::getPlayer(void) {
	return player;
}