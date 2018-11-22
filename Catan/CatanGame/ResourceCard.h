#pragma once

/*
* ResourceCard
* Clase modelo con informacion de las cartas de recursos
*/
class ResourceCard {
public:

	/* Constructores y destructores */
	ResourceCard();
	ResourceCard(unsigned int resourceId);

	/* 
	* getResourceId
	* Devuelve tipo de recurso
	*/
	unsigned int getResourceId();

	/*
	* getPlayerId
	* Devuelve player a quien pertenece la carta
	*/
	unsigned int getPlayerId();

	/* Setters de atributos de la clase */
	void setResourceId(unsigned int resourceId);
	void setPlayerId(unsigned int playerId);

private:
	unsigned int resourceId;
	unsigned int playerId;
};
