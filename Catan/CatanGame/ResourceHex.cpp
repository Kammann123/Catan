#include "ResourceHex.h"

ResourceHex::
ResourceHex(ResourceId resource_, unsigned int token_, unsigned char coord_)
{
	this->resource = resource_;
	this->token = token_;
	this->coord = coord_;
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