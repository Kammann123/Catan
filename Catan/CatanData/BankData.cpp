#include "BankData.h"

BankData::
BankData(list<ResourceId> given, list<ResourceId> recv) : CatanData(CatanData::Type::BANK) {
	this->given = given;
	this->recv = recv;
}

BankData::
BankData(list<ResourceCard*> given, list<ResourceId> recv) : CatanData(CatanData::Type::BANK) {
	this->givenCard = given;
	this->recv = recv;
}

BankData::
BankData(void) : CatanData(CatanData::Type::BANK) {}

void 
BankData::addGiven(ResourceId res) {
	this->given.push_back(res);
}

void
BankData::addReceived(ResourceId res) {
	this->recv.push_back(res);
}

list<ResourceId>&
BankData::getGiven(void) {
	return this->given;
}

list<ResourceId>&
BankData::getRecv(void) {
	return this->recv;
}

bool
BankData::isBankTrade(void) {
	return (given.size() == 4 && recv.size() == 1);
}

bool
BankData::isDockTrade(void) {
	return (given.size() == 3 || given.size() == 2) && recv.size() == 1;
}
