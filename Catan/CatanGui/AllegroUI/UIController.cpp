#include "UIController.h"

UIController::
UIController(UIModel* model, Id id) {
	this->model = model;
	this->id = id;
	this->enable = true;
}

UIController::
~UIController() {}

UIModel*
UIController::getModel(void) {
	return this->model;
}

UIController::Id
UIController::getId(void) {
	return this->id;
}

void
UIController::setEnable(bool status) {
	this->enable = status;
}

bool
UIController::getEnable(void) {
	return this->enable;
}