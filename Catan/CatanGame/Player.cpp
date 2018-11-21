#include "Player.h"

Player::Player(string name, PlayerId id)
{
	this->id = id;
	this->name = name;
	victoryPoints = 0;
	resourceCards = {};
	for (int i = 0; i < SETTLEMENTS_QTY; i++)
	{
		settlements.push_back(new Building(id, SETTLEMENT));
	}
	for (int i = 0; i < ROADS_QTY; i++)
	{
		roads.push_back(new Building(id, ROAD));
	}
	for (int i = 0; i < CITIES_QTY; i++)
	{
		cities.push_back(new Building(id, CITY));
	}
}

Player::~Player()
{
	while (!cities.empty())
	{
		delete cities.front();
		cities.pop_front();
	}
	while (!settlements.empty())
	{
		delete settlements.front();
		settlements.pop_front();
	}
	while (!roads.empty())
	{
		delete roads.front();
		roads.pop_front();
	}
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

Building * Player::getSettlement()
{
	Building * set = settlements.front();
	settlements.pop_front();
	return set;
}

Building * Player::getCity()
{
	Building * set = cities.front();
	cities.pop_front();
	return set;
}

Building * Player::getRoad()
{
	Building * set = roads.front();
	roads.pop_front();
	return set;
}
