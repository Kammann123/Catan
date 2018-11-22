#pragma once
#include "Player.h"
#include "../CatanNetworking/NetworkPackets/NetworkPacket.h"

/*
* ResourceCard
* Clase modelo con informacion de las cartas de recursos
*/
class ResourceCard {
public:

	/* Constructores y destructores */
	ResourceCard();
	ResourceCard(ResourceId resourceId);

	/* 
	* getResourceId
	* Devuelve tipo de recurso
	*/
	ResourceId getResourceId();

	/*
	* getPlayerId
	* Devuelve player a quien pertenece la carta
	*/
	PlayerId getPlayerId();

	/* Setters de atributos de la clase */
	void setResourceId(ResourceId resourceId);
	void setPlayerId(PlayerId playerId);

private:
	ResourceId resourceId;
	PlayerId playerId;
};
