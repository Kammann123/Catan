#include "CatanError.h"

CatanError::
CatanError()
{
	this->ID = ErrorID::NO_ERROR;
	this->description = "No Error";
	this->source = PlayerId::PLAYER_ONE; // por defecto, es el jugador 1 (?)
}

CatanError::
~CatanError()
{
}

ErrorID CatanError::
getID(void)
{
	return ID;
}

void CatanError::setID(ErrorID newID)
{
	this->ID = newID;
}

string& CatanError::
getDescription(void)
{
	return this->description;
}

void CatanError::
setDescription(string & newDescription)
{
	this->description = newDescription;
}
