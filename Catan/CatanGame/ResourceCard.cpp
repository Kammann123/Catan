#include "ResourceCard.h"
#include "Player.h"

ResourceCard::ResourceCard(ResourceId resourceId)
{
	this->resourceId = resourceId;
}

ResourceCard::ResourceCard(PlayerId player, ResourceId resourceId)
{
	this->playerId = player;
	this->resourceId = resourceId;
}

ResourceId ResourceCard::getResourceId()
{
	return resourceId;
}

const char* ResourceCard::getResource(void) {
	return resourceStrings[(unsigned int)resourceId];
}

PlayerId ResourceCard::getPlayerId()
{
	return playerId;
}

void ResourceCard::setResourceId(ResourceId resourceId)
{
	this->resourceId = resourceId;
}

void ResourceCard::setPlayerId(PlayerId playerId)
{
	this->playerId = playerId;
}
