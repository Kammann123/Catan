#pragma once

#include "ProtocolTag.h"

/*
* StringTag
* Crea un tag en funcion de un string invariante.
*/
class StringTag : public ProtocolTag {
public:
	StringTag(string tag);
	virtual string getTag(void);
private:
	string tag;
};