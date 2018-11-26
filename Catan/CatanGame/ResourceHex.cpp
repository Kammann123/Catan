#include "ResourceHex.h"

ResourceHex::
ResourceHex(ResourceId resource_, unsigned int token_, Coord coord_){
	this->resource = resource_;
	this->token = token_;
	this->coord = coord_;
}

ResourceHex::
ResourceHex(ResourceId resource_, Coord coord_){
	this->resource = resource_;
	this->coord = coord_;
}

ResourceHex::
ResourceHex(Coord coord_){
	this->coord = coord_;
}

ResourceHex::
ResourceHex(const ResourceHex& copy) {
	this->resource = copy.resource;
	this->token = copy.token;
	this->coord = copy.coord;
}

unsigned int
ResourceHex::getToken(void)
{
	return token;
}

void
ResourceHex::setToken(unsigned int newToken)
{
	if (isValidToken(newToken))
	{
		token = newToken;
	}

}

void
ResourceHex::setCoord(Coord coord) {
	this->coord = coord;
}

ResourceId
ResourceHex::getResource(void)
{
	return resource;
}

void
ResourceHex::setResource(ResourceId newResource)
{
	resource = newResource;
}

Coord
ResourceHex::getCoord(void)
{
	return coord;
}