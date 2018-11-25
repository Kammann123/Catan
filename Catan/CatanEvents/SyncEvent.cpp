#include "SyncEvent.h"

SyncEvent::
SyncEvent(Sources source) : CatanEvent(Events::SYNC, source, PlayerId::PLAYER_TWO) {}

void 
SyncEvent::setLocalName(NameData name) {
	local = name;
}

void 
SyncEvent::setRemoteName(NameData name) {
	remote = name;
}

void 
SyncEvent::setMap(MapData map) {
	this->map = map;
}

void 
SyncEvent::setTokens(TokenData tokens) {
	this->tokens = tokens;
}

void 
SyncEvent::setDevCards(DevCardsData cards) {
	this->devs = cards;
}

void 
SyncEvent::setDevMode(bool mode) {
	this->withDevs = mode;
}

void 
SyncEvent::setTurn(PlayerId player) {
	this->turn = player;
}

NameData 
SyncEvent::getLocalName(void) {
	return local;
}

NameData 
SyncEvent::getRemoteName(void) {
	return remote;
}

MapData 
SyncEvent::getMap(void) {
	return map;
}

TokenData 
SyncEvent::getTokens(void) {
	return tokens;
}

DevCardsData 
SyncEvent::getDevCards(void) {
	return devs;
}

PlayerId 
SyncEvent::getTurn(void) {
	return turn;
}

bool 
SyncEvent::hasDevs(void) {
	return withDevs;
}