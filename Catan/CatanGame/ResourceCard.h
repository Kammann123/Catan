#pragma once

#include "../CatanData/CatanData.h"

enum class PlayerId;

/*
* ResourceCard
* Clase modelo con informacion de las cartas de recursos
*/
class ResourceCard {
public:

	/* Constructores y destructores */
	ResourceCard(ResourceId resourceId);
	ResourceCard(PlayerId player, ResourceId resourceId);

	/* 
	* getResourceId
	* Devuelve tipo de recurso
	*/
	ResourceId getResourceId(void);

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
