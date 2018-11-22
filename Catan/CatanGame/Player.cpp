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

bool Player::hasRoads(void)
{
	bool ret = true;
	if()
}
