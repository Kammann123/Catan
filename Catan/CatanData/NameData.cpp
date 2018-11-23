#include "NameData.h"

NameData::
NameData(string name) : CatanData(CatanData::Type::NAME) {
	this->name = name;
}

NameData::
NameData() : CatanData(CatanData::Type::NAME) {
	this->name = "";
}

void
NameData::setName(string name) {
	this->name = name;
}

void
NameData::setName(unsigned char name) {
	this->name += name;
}

string 
NameData::getName(void) {
	return this->name;
}