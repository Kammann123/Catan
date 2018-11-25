#include "Player.h"

Player::Player(PlayerId player) {

	unsigned int settleCount = SETTLEMENT_COUNT;
	unsigned int roadsCount = ROAD_COUNT;
	unsigned int citiesCount = CITY_COUNT;

	/* Inicializacion */
	this->name = "";
	this->player = player;
	victoryPoints = 0;
	resourceCards = {};

	/* Agrego settlements */
	while (settleCount) {
		/* Creo el settlement */
		Building* settlement = new Building(player, BuildingType::SETTLEMENT);
		this->settlements.push_back(settlement);
		settleCount--;
	}

	/* Agrego roads */
	while (roadsCount) {
		/* Creo el road */
		Building* road = new Building(player, BuildingType::ROAD);
		this->roads.push_back(road);
		roadsCount--;
	}

	/* Agrego cities */
	while (citiesCount) {
		/* Creo el city */
		Building* city = new Building(player, BuildingType::CITY);
		this->cities.push_back(city);
		citiesCount--;
	}
}

Player::Player(PlayerId player, string name, unsigned int settleCount, unsigned int citiesCount, unsigned int roadsCount)
{
	/* Inicializacion */
	this->name = name;
	this->player = player;
	victoryPoints = 0;
	resourceCards = {};

	/* Agrego settlements */
	while (settleCount) {
		/* Creo el settlement */
		Building* settlement = new Building(player, BuildingType::SETTLEMENT);
		this->settlements.push_back(settlement);
		settleCount--;
	}

	/* Agrego roads */
	while (roadsCount) {
		/* Creo el road */
		Building* road = new Building(player, BuildingType::ROAD);
		this->roads.push_back(road);
		roadsCount--;
	}

	/* Agrego cities */
	while (citiesCount) {
		/* Creo el city */
		Building* city = new Building(player, BuildingType::CITY);
		this->cities.push_back(city);
		citiesCount--;
	}
}

Player::~Player() {
	for (Building* b : settlements) {
		delete b;
	}
	for (Building* b : roads) {
		delete b;
	}
	for (Building* b : cities) {
		delete b;
	}
	for (ResourceCard* r : resourceCards) {
		delete r;
	}
}

void 
Player::setName(string name) {
	this->name = name;
}

string Player::getName()
{
	return name;
}

unsigned int Player::getVictoryPoints()
{
	return victoryPoints;
}

unsigned int
Player::getResourceCount(ResourceId resourceID) const {
	unsigned int resourceCount = 0;

	for (ResourceCard* resCard : this->resourceCards) {
		if (resCard->getResourceId() == resourceID) {
			resourceCount++;
		}
	}

	return resourceCount;
}

void Player::addPoints(unsigned int points)
{
	victoryPoints += points;
}

void Player::removePoints(unsigned int points)
{
	victoryPoints -= points;
}

void Player::addResourceCard(ResourceCard * card)
{
	resourceCards.push_back(card);
}

void Player::removeResourceCard(ResourceCard * card)
{
	resourceCards.remove(card);
}

unsigned int Player::hasRoads(void)
{
	bool ret = true;
	if (roads.size() == 0)
	{
		ret = false;
	}
	return ret;

}

unsigned int Player::hasSettlements(void)
{
	bool ret = true;
	if (settlements.size() == 0)
	{
		ret = false;
	}

	return ret;
}

unsigned int Player::hasCities(void)
{
	bool ret = true;
	if (cities.size() == 0)
	{
		ret = false;
	}

	return ret;
}

void
Player::removeResourceCard(ResourceId resourceId, unsigned int qty) {

	list<ResourceCard*> bucket;

	/* Verifico tener esa cantidad para removerlas */
	if( qty == getResourceCount(resourceId) ){
		/* Busco y guardo las cartas que tengo que tirar */
		for (ResourceCard* card : resourceCards) {
			if (card->getResourceId() == resourceId) {
				bucket.push_back(card);
				qty--;
				if (qty == 0)	break;
			}
		}
		/* Tiro las cartas */
		for (ResourceCard* card : bucket) {
			resourceCards.remove(card);
			delete card;
		}
	}
}

list<ResourceCard*>
Player::giveResourceCard(ResourceId resourceId, unsigned int qty) {
	list<ResourceCard*> bucket;

	/* Busco hasta esa cantidad */
	for (ResourceCard* card : resourceCards) {
		if (card->getResourceId() == resourceId) {
			bucket.push_back(card);
			qty--;
			if (qty == 0) break;
		}
	}
	/* Las quito de mi lista */
	for (ResourceCard* card : bucket) {
		resourceCards.remove(card);
	}

	return bucket;
}

void
Player::giveBackBuilding(BuildingType type, Building* building) {

	/* Si la construccion existe realmente */
	if (building) {

		/* La vuelvo a meter a mis conjuntos */
		switch (type) {
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

Building* Player:: popRoad(void)
{
	Building* ret = nullptr;

	if (hasRoads())
	{
		ret = roads.back(); // tomo ultimo elemento de la lista
		roads.pop_back(); // elimino ultimo elemento de la lista
	}

	return ret; // devuelvo puntero
}

Building* Player::popSettlement(void)
{
	Building* ret = nullptr;

	if (hasSettlements())
	{
		ret = settlements.back(); // tomo ultimo elemento de la lista
		settlements.pop_back(); // elimino ultimo elemento de la lista
	}

	return ret; // devuelvo puntero
}


Building* Player::popCity(void)
{
	Building* ret = nullptr;

	if (hasCities())
	{
		ret = cities.back(); // tomo ultimo elemento de la lista
		cities.pop_back(); // elimino ultimo elemento de la lista
	}

	return ret; // devuelvo puntero
}

