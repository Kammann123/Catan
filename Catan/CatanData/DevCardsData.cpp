#include "DevCardsData.h"

DevCardsData::
DevCardsData(list<DevCardId> cards) : CatanData(CatanData::Type::DEV_CARDS) {
	this->cards = cards;
}

DevCardsData::
DevCardsData(void) : CatanData(CatanData::Type::DEV_CARDS) {}

bool
DevCardsData::setCard(DevCardId card) {

	if (cards.size() < MAX_CARDS) {
		cards.push_back(card);
		return true;
	}
	return false;
}

list<DevCardId>&
DevCardsData::getCards(void) {
	return cards;
}