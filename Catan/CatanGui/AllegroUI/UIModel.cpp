#include "UIModel.h"

UIModel::
UIModel() {}

UIModel::
~UIModel() {}

void 
UIModel::setVisible(bool visibleStatus) {
	this->visible = visibleStatus;
}

void 
UIModel::setEnable(bool enableStatus) {
	this->enable = enableStatus;
}

bool 
UIModel::getVisible(void) {
	return this->visible;
}

bool 
UIModel::getEnable(void) {
	return this->enable;
}