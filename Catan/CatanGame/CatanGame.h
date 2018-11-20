#pragma once
#include "Player.h"
#include "Map.h"
#include "ResourceCard.h"
#include "../CatanError/CatanError.h"
#include <string>

using namespace std;

enum  States{};
enum  Events{ THROW_DICE };
enum  Sources{ NETWORKING, GUI, GAME };
class CatanGame {

public:
	CatanGame() {};
	~CatanGame() {};
	CatanError& throwDice(Sources source, PlayerId player, unsigned int diceOne, unsigned int diceTwo);
	CatanError& buildSettlement(Sources source, PlayerId player, string place);
	CatanError& buildRoad(Sources source, PlayerId player, string place);
	CatanError& buildCity(Sources source, PlayerId player, string place);
	CatanError& pass(Sources source, PlayerId player);
	CatanError& playerExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven,list<ResourceCard*>& cardsReceived);
	CatanError& dockExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven, list<ResourceCard*>& cardsReceived);
	CatanError& bankExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven, list<ResourceCard*>& cardsReceived);
	CatanError& robberCards(Sources source, PlayerId player, list<ResourceCard*>& cards);
	CatanError& robberMove(Sources source, PlayerId player,string destination);



	Player& getLocalPlayer(void); // getter del jugador local
	Player& geNetworkPlayer(void); // getter del jugador remoto

private:
	Player& localPlayer; // clase que contiene los datos del jugador local
	Player& networkPlayer; // clase que contiene los datos del jugador remoto
	PlayerId longestRoad; // variable que informa qué jugador tiene el longest road
	// mapa



};