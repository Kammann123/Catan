#include "ResourceHex.h"

ResourceHex::
ResourceHex() : FrameUI("", 0, 0) {}

ResourceHex::
ResourceHex(ResourceId resource) : FrameUI("", 0, 0) {
	this->resource = resource;
}

ResourceHex::
ResourceHex(const ResourceHex& copy) : FrameUI("", 0, 0) {
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