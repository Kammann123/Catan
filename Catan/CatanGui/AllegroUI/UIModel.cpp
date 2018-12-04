#include "UIModel.h"

UIModel::
UIModel(string id, bool UIDestroys) {
	this->id = id;
	this->visible = false;
	this->enable = false;
	this->UIDestroys = UIDestroys;
}

UIModel::
~UIModel() {}

void 
UIModel::setVisible(bool visibleStatus) {
	this->visible = visibleStatus;
	notifyObservers();
}

void 
UIModel::setEnable(bool enableStatus) {
	this->enable = enableStatus;
	notifyObservers();
}

void 
UIModel::setUIDestroy(bool destroys) {
	this->UIDestroys = destroys;
}

bool 
UIModel::getVisible(void) {
	return this->visible;
}

bool 
UIModel::getEnable(void) {
	return this->enable;
}

void
UIModel::setId(string id) {
	this->id = id;
}

string
UIModel::getId(void) {
	return id;
}

bool
UIModel::shouldUIDestroy(void) {
	return UIDestroys;
}