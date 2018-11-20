#include "ResourceCard.h"

ResourceCard::ResourceCard()
{
	resourceId = 0;
	playerId = 0;
}

ResourceCard::ResourceCard(unsigned int resourceId)
{
	this->resourceId = resourceId;
}

unsigned int ResourceCard::getResourceId()
{
	return resourceId;
}

unsigned int ResourceCard::getPlayerId()
{
	return playerId;
}

void ResourceCard::setResourceId(unsigned int resourceId)
{
	this->resourceId = resourceId;
}

void ResourceCard::setPlayerId(unsigned int playerId)
{
	this->playerId = playerId;
}
