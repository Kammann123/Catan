#include "ResourceHex.h"

ResourceHex::
ResourceHex() {}

ResourceHex::
ResourceHex(ResourceId resource) {
	this->resource = resource;
}

ResourceHex::
ResourceHex(const ResourceHex& copy) {
	this->resource = copy.resource;
	this->token = copy.token;
	this->coord = copy.coord;
}

Coord
ResourceHex::getCoord(void)
{
	return coord;
}

const char*
ResourceHex::getLand(void) {
	return landStrings[(unsigned int)resource];
}

unsigned int
ResourceHex::getToken(void)
{
	return token;
}

ResourceId
ResourceHex::getResource(void)
{
	return resource;
}

void
ResourceHex::place(Coord coord) {
	this->coord = coord;
}

void
ResourceHex::setToken(unsigned int newToken)
{
	if (isValidToken(newToken))
	{
		token = newToken;
	}
}