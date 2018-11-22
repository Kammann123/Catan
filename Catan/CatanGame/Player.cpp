#include "Player.h"

Player::Player(string name, unsigned int settleCount, unsigned int citiesCount, unsigned int roadsCount)
{
	/*
	 crear los buildings de las listas acá
	*/
	this->name = name;
	victoryPoints = 0;
	resourceCards = {};
	settlements = 0;
	cities = 0;
	roads = 0;
}

string Player::getName()
{
	return name;
}

unsigned int Player::getVictoryPoints()
{
	return victoryPoints;
}

list<ResourceCard*>* Player::getResourceCards()
{
	return &resourceCards;
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

