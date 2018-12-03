#pragma once

#include "../CatanData/CatanData.h"
#include "../CatanGui/AllegroUI/FrameUI.h"

class Player;
class CatanGame;

/*
* ResourceCard
* Clase modelo con informacion de las cartas de recursos
*/
class ResourceCard : public FrameUI {
public:

	/*
	* ResourceCard - Se construye con, a lo sumo, el tipo de carta
	* de recursos que corresponde, y puntero al CatanGame, debe 
	* conocerlo, por quien define su status de estar en el mazo.
	*/
	ResourceCard(ResourceId resourceId, CatanGame* game);

	/*
	*  assign y desa - Permite modificar el estado de la carta,
	* con lo cual se la asigna a un jugador determinado,
	* en base a lo cual modifica su posicion relativa al tablero.
	* En caso de tomar el parametro por defecto, vuelve al mazo.
	*/
	void assign(Player* player = nullptr);

	/*
	* getters - Permiten acceder y leer la informacion actual
	* de la carta.
	*/
	ResourceId getResourceId(void);
	const char* getResource(void);
	Player* getPlayer(void);

private:

	ResourceId id;
	Player* player;
	CatanGame* game;
};
