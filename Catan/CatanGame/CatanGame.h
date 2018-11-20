#pragma once
#include "Player.h"
#include "Map.h"
#include "ResourceCard.h"
#include <string>

using namespace std;

enum  States{};
enum  Events{ THROW_DICE };
enum  Sources{ NETWORKING, GUI, GAME };
class CatanGame {

public:
	CatanGame() {};
	~CatanGame() {};
	void throwDice(Sources source, PlayerId player, unsigned int diceOne, unsigned int diceTwo);
	void buildSettlement(Sources source, PlayerId player, string place);
	void buildRoad(Sources source, PlayerId player, string place);
	void buildCity(Sources source, PlayerId player, string place);
	void pass(Sources source, PlayerId player);
	void playerExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven,list<ResourceCard*>& cardsReceived);
	void dockExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven, list<ResourceCard*>& cardsReceived);
	void bankExchange(Sources source, PlayerId playerFrom, PlayerId playerTo, list<ResourceCard*>& cardsGiven, list<ResourceCard*>& cardsReceived);
	void robberCards(Sources source, PlayerId player, list<ResourceCard*>& cards);
	void robberMove(Sources source, PlayerId player,string destination);



	Player& getLocalPlayer(void); // getter del jugador local
	Player& geNetworkPlayer(void); // getter del jugador remoto

private:
	Player& localPlayer; // clase que contiene los datos del jugador local
	Player& networkPlayer; // clase que contiene los datos del jugador remoto
	PlayerId longestRoad; // variable que informa qué jugador tiene el longest road
	// mapa



};