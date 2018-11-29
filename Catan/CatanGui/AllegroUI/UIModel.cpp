#include "UIModel.h"

UIModel::
UIModel() {}

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

bool 
UIModel::getVisible(void) {
	return this->visible;
}

bool 
UIModel::getEnable(void) {
	return this->enable;
}