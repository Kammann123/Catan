#include "BankData.h"

BankData::
BankData(list<ResourceId> given, list<ResourceId> recv) : CatanData(CatanData::Type::BANK) {
	this->given = given;
	this->recv = recv;
}

BankData::
BankData(list<ResourceCard*> given, list<ResourceCard*> recv) {
	this->givenCard = given;
	this->recvCard = recv;
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

void
BankData::addGiven(ResourceCard* res) {
	givenCard.push_back(res);
}

void 
BankData::addReceived(ResourceCard* res) {
	recvCard.push_back(res);
}

list<ResourceCard*>&
BankData::getGivenCards(void) {
	return givenCard;
}

list<ResourceCard*>&
BankData::getRecvCards(void) {
	return recvCard;
}

bool
BankData::isBankTrade(void) {
	return (givenCard.size() == 4 && recvCard.size() == 1);
}

bool
BankData::isDockTrade(void) {
	return ((givenCard.size() == 3 || givenCard.size() == 2) && recvCard.size() == 1);
}