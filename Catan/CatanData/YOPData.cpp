#include "YOPData.h"

YOPData::
YOPData(ResourceId fRes, ResourceId sRes) : CatanData(CatanData::Type::YOP) {
	this->fResource = fRes;
	this->sResource = sRes;
}

YOPData::
YOPData() : CatanData(CatanData::Type::YOP) {}

void
YOPData::setFirstResource(ResourceId res) {
	this->fResource = res;
}

void
YOPData::setSecondResource(ResourceId res) {
	this->sResource = res;
}

ResourceId
YOPData::getFirstResource(void) {
	return this->fResource;
}

ResourceId
YOPData::getSecondResource(void) {
	return this->sResource;
}