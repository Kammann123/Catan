#include "ResourceHex.h"

ResourceHex::
ResourceHex(ResourceId resource_, unsigned int token_, unsigned char coord_){
	this->resource = resource_;
	this->token = token_;
	this->coord = coord_;
}

ResourceHex::
ResourceHex(ResourceId resource_, unsigned char coord_){
	this->resource = resource_;
	this->coord = coord_;
}

ResourceHex::
ResourceHex(unsigned char coord_){
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
ResourceHex::setCoord(unsigned char coord) {
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

unsigned char 
ResourceHex::getCoord(void)
{
	return coord;
}