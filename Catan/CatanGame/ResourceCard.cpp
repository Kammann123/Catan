#include "ResourceCard.h"
#include "Player.h"

ResourceCard::ResourceCard()
{
	resourceId = ResourceId::DESERT; // esto por defecto ?????
	playerId = PlayerId::PLAYER_ONE; // esto por defecto ?????
}

ResourceCard::ResourceCard(ResourceId resourceId)
{
	this->resourceId = resourceId;
}

ResourceId ResourceCard::getResourceId()
{
	return resourceId;
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
