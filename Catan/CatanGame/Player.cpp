#include "Player.h"
#include "../CatanGui/CatanLauncher/GameWindow/GameWindow.h"

void 
Player::_create_settlements(void) {	
	for (unsigned int i = 0; i < SETTLEMENT_COUNT; i++) {
		Building* building = new Building(this, BuildingType::SETTLEMENT);
		settlements.push_back(building);
	}
}

void
Player::_create_roads(void) {
	for (unsigned int i = 0; i < ROAD_COUNT; i++) {
		Building* building = new Building(this, BuildingType::ROAD);
		settlements.push_back(building);
	}
}

void
Player::_create_cities(void){
	for (unsigned int i = 0; i < CITY_COUNT; i++) {
		Building* building = new Building(this, BuildingType::CITY);
		settlements.push_back(building);
	}
}

void
Player::_destroy_settlements(void) {
	for (Building* building : settlements) {
		if (building) {
			delete building;
		}
	}
}

void
Player::_destroy_roads(void) {
	for (Building* building : roads) {
		if (building) {
			delete building;
		}
	}
}

void
Player::_destroy_cities(void) {
	for (Building* building : cities) {
		if (building) {
			delete building;
		}
	}
}

void
Player::_destroy_cards(void) {
	for (ResourceCard* card : resourceCards) {
		if (card) {
			delete card;
		}
	}
}

Player::
Player(PlayerId player, CatanGame* game) : ContainerUI(player == PlayerId::PLAYER_ONE ? PLAYER_ONE_ID : PLAYER_TWO_ID, 0, 0) {
	/* Inicializacion de parametros */
	this->player = player;
	this->game = game;
	this->name = player == PlayerId::PLAYER_ONE ? "PlayerOne" : "PlayerTwo";
	this->victoryPoints = 0;
	this->resourceCards.clear();
	this->settlements.clear();
	this->cities.clear();
	this->roads.clear();

	/* Creacion de fichas */
	_create_settlements();
	_create_cities();
	_create_roads();
}

Player::
~Player(void) {
	/* Libero y destruyo elementos */
	_destroy_settlements();
	_destroy_cities();
	_destroy_roads();
	_destroy_cards();
}

void 
Player::setName(string name) {
	this->name = name;
}

unsigned int
Player::getResourceCount(ResourceId resourceID) const {
	unsigned int resourceCount = 0;

	for (ResourceCard* card : resourceCards) {
		if (card->getResourceId() == resourceID) {
			resourceCount++;
		}
	}
	return resourceCount;
}

unsigned int
Player::getResourceCount(void) const {
	return (unsigned int)this->resourceCards.size();
}

list<Building*>
Player::buildings(BuildingType type) {
	switch (type) {
		case BuildingType::SETTLEMENT:
			return settlements;
			break;
		case BuildingType::ROAD:
			return roads;
			break;
		case BuildingType::CITY:
			return cities;
			break;
	}

	return {};
}

unsigned int Player::getVictoryPoints()
{
	return victoryPoints;
}

list<ResourceCard*>
Player::showCards(void) {
	return resourceCards;
}

unsigned int Player::hasRoads(void)
{
	return (unsigned int)roads.size();
}

unsigned int Player::hasSettlements(void)
{
	return (unsigned int)settlements.size();
}

unsigned int Player::hasCities(void)
{
	return (unsigned int)cities.size();
}

PlayerId
Player::getPlayerId(void) {
	return player;
}

string Player::getName()
{
	return name;
}

void Player::removePoints(unsigned int points)
{
	victoryPoints -= points;
}

void Player::addPoints(unsigned int points)
{
	victoryPoints += points;
}

void
Player::resetVictoryPoints() {
	this->victoryPoints = 0;
}

list<ResourceCard*>
Player::giveAllCards(void) {
	list<ResourceCard*> temp = resourceCards;
	removeCard(temp);
	return temp;
}

list<ResourceCard*> 
Player::giveCards(list<ResourceId> ids) {
	list<ResourceCard*> cards;
	for (ResourceId id : ids) {
		cards.push_back(giveCard(id));
	}
	return cards;
}

list<ResourceCard*>
Player::giveCards(ResourceId id, unsigned int qty) {
	list<ResourceCard*> cards;
	while (qty) {
		ResourceCard* card = giveCard(id);
		if (card) {
			cards.push_back(card);
		}
		qty--;
	}
	return cards;
}

ResourceCard*
Player::giveCard(ResourceId id) {
	for (ResourceCard* card : resourceCards) {
		if (card->getResourceId() == id) {
			card->assign();
			notifyObservers();
			return card;
		}
	}
	return nullptr;
}

void
Player::removeCard(list<ResourceCard*> cards) {
	for (ResourceCard* card : cards) {
		removeCard(card);
	}
}

void
Player::removeCard(ResourceCard* card) {
	card->assign();
	resourceCards.remove(card);
	notifyObservers();
}

void
Player::addCard(list<ResourceCard*> cards) {
	for (ResourceCard* card : cards) {
		addCard(card);
	}
}

void
Player::addCard(ResourceCard* card) {
	card->assign(this);
	resourceCards.push_back(card);
	notifyObservers();
}

void
Player::giveBackBuilding(Building* building) {
	if (building) {
		switch (building->getType()) {
			case BuildingType::CITY:
				cities.push_back(building);
				break;
			case BuildingType::ROAD:
				roads.push_back(building);
				break;
			case BuildingType::SETTLEMENT:
				settlements.push_back(building);
				break;
		}
	}
}

Building* Player::popRoad(void)
{
	if (hasRoads()) {
		Building* temp = roads.back();
		roads.pop_back();
		return temp;
	}
	return nullptr;
}

Building* Player::popSettlement(void)
{
	if (hasSettlements()) {
		Building* temp = settlements.back();
		settlements.pop_back();
		return temp;
	}
	return nullptr;
}


Building* Player::popCity(void)
{
	if (hasCities()) {
		Building* temp = cities.back();
		cities.pop_back();
		return temp;
	}
	return nullptr;
}