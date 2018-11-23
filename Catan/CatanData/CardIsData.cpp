#include "CardIsData.h"

CardIsData::
CardIsData(ResourceId res) : CatanData(CatanData::Type::CARD_IS) {
	this->resource = res;
}

CardIsData::
CardIsData() : CatanData(CatanData::Type::CARD_IS) {}

void
CardIsData::setResource(ResourceId res) {
	resource = res;
}

ResourceId
CardIsData::getResource(void) {
	return resource;
}